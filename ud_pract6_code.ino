//------------------------------------------
// Определение пинов

#define Trig 8
#define Echo 7
#define RedLED 13
#define GreenLED 12
#define YellowLED 11
#define BlueLED 10

// -----------------------------------------
// Начальные значения

double distance;
double x = 250;
double y = 50;
int a = 200;
int b = 150;
int c = 100;
int com_0 = 0, com_1 = 0, com_2 = 0;

// -----------------------------------------
// Настройка, приветствие и команды

void setup() 				{
  
  Serial.begin (115200);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  Serial.println("Hello there!");
  Serial.println("You can use commands!");
  Serial.println("List:");
  Serial.println("1 - to start or pause");      // старт/пауза системы
  Serial.println("2 - to print the distance");  // вывод дистанции
  Serial.println("3 - to show the thresholds"); // вывод порогов
  Serial.println("4 - to set the thresholds");  // изменение порогов
							}

// -----------------------------------------
// Определение дистанции

void dist() 				{
  
  int duration;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration / 58;
							}

// -----------------------------------------
// Вывод дистанции
  
void distfeed()		   		{
  
  while (com_1)				{
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  break;
  							}}

// -----------------------------------------
// Мигание светодиодами
  
void blink() 				{
  
  while (com_0) 			{
    if (distance < y || distance > x){
    digitalWrite(BlueLED, LOW); 
    digitalWrite(GreenLED, LOW); 
    digitalWrite(YellowLED,LOW);
    digitalWrite(RedLED,LOW);
      distfeed();
    dist();
    break;
							}
    if (distance < c){
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, HIGH); 
    digitalWrite(YellowLED,HIGH);
    digitalWrite(BlueLED,HIGH);
      distfeed();
    dist();
    break;
							}
   
    if (distance < b)   	{
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, HIGH); 
    digitalWrite(YellowLED,HIGH);
    digitalWrite(BlueLED,LOW);
      distfeed();
    dist();
    break;
  							}
    
    if (distance < a) 		{
    digitalWrite(RedLED, HIGH);
    digitalWrite(GreenLED, HIGH); 
    digitalWrite(YellowLED,LOW);
    digitalWrite(BlueLED,LOW);
      distfeed();
    dist();
    break;
							}
      
    if (distance < x)  		{
    digitalWrite(RedLED,HIGH);
    digitalWrite(GreenLED,LOW); 
    digitalWrite(YellowLED,LOW);
    digitalWrite(BlueLED,LOW);
      distfeed();
    dist();
    break;
  							}}}

// -----------------------------------------
// Вывод пороговых значений

void porog_print()			{
 
  	Serial.print("Far threshold: ");
    Serial.println(x);
    Serial.print("Nigh threshold: ");
    Serial.println(y);						
							}

// -----------------------------------------
// Настройка пороговых значений

void porog_change()			{ 
  	
  	char in[10]; 
  	int x_t, y_t;
	Serial.println("Type the new x");  
  	int i = 0;
  	while(true)				{
    
	if(Serial.available())	{
  	for (i = 0; i < 4; i++)	{
  	in[i] = Serial.read();
  	delay(10);
    						}
 	x_t = atoi(in);
    if (1 < x_t < 300) 			{
  	Serial.print("New far threshold: ");
    x = x_t; Serial.println(x); 
    						}
    else 					{
    Serial.println("Check the input");
    						}
  	break;
  							}}
  
  	Serial.println("Type the new y");  
  	while(true)				{
    
	if(Serial.available())	{
  	for (i = 0; i < 4; i++)	{
  	in[i] = Serial.read();
  	delay(10);
    						}
 	y_t = atoi(in);
    if (0 <= y_t < x) 			{
  	Serial.print("New nigh threshold: ");
    y = y_t; Serial.println(y); 
    						}
    else 					{
    Serial.println("Check the input");
    						}
  	break;
  							}}
  	a = y + (x-y)*0.75;
    b = y + (x-y)*0.5;
    c = y + (x-y)*0.25;
							}

// -----------------------------------------
// Изменение командных чисел

void com_num()				{

int i, command;
while(Serial.available()) 	{
  	char in[10];
    for (i = 0; i < 1; i++)	{
    in[i] = Serial.read();
    if (in[i] < 48 || in[i] > 50)
    						{
    	Serial.println("wrong command");
    	break;
    						}}
	command = atoi(in);
	if(command > 3) 		{
    	Serial.println("Check the input");
    	break;
							}
	switch(command)			{
  	case 1: if(com_0 == 1) 
    		{com_0 = 0; Serial.println("System paused");} 
			else 
            {com_0 = 1; Serial.println("System is working");}
			break;
    case 2: if(com_1 == 1) 
    		{com_1 = 0; Serial.println("Distance data paused");} 
			else 
            {com_1 = 1; Serial.println("Distance data resumed");}
			break;
	case 3: Serial.println("-- Thresholds -- ");
      		porog_print();
			break;
	case 4: Serial.println("-- Setting the thresholds -- ");
      		porog_change();
			break;
        					}}}

// -----------------------------------------
// Основная часть
  
void loop() 				{
  	
  	com_num();
  	blink();
  	delay(100);
							}

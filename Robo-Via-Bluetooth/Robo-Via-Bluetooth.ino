// Define os pinos de utilização do Driver L298.
const int motorA1 = 8;    // Pin  5 of L293.
const int motorA2 = 9;    // Pin  6 of L293.
const int motorB1 = 10;    // Pin 10 of L293.
const int motorB2 = 11;    // Pin  9 of L293.

const int BTState = 0;    // Define o pino 0 como o pino de comunicação do Bluetooth.

// Variáveis úteis
int state_rec;
int vSpeed = 200;         // Define velocidade padrão 0 < x < 255.
char state;

void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(BTState, INPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  Serial.println("-- USINAINFO --");
  Serial.println("Carrinho Arduino controlado por Smartphone");
}

void loop() {

  // Para o carro quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state = 'S';
  }


  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }

  // Altera a velocidade de acordo com valores especificados.
  switch (state) {
    case '0':
      vSpeed = 0;
      break;
    case '4':
      vSpeed = 100;
      break;
    case '6':
      vSpeed = 155;
      break;
    case '7':
      vSpeed = 180;
      break;
    case '8':
      vSpeed = 200;
      break;
    case '9':
      vSpeed = 230;
      break;
    case 'q':
      vSpeed = 255;
      break;
  }

  // Controle do movimento do carro
  switch (state) {
    case 'L':   // Esquerda
      Serial.println(state);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB2, 0);
      break;

    case 'H':   // Trás Esquerda
      Serial.println(state);
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 100);
      analogWrite(motorB2, 0);
      break;

    case 'G':   // Frente Esquerda
      Serial.println(state);
      analogWrite(motorA1, 100);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorB2, 0);
      break;

    case 'R':   // Direita
      Serial.println(state);
      analogWrite(motorA1, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, vSpeed);
      analogWrite(motorA2, vSpeed);
      break;

    case 'I':   // Frente Direita
      Serial.println(state);
      analogWrite(motorA1, 0);
      analogWrite(motorA2, vSpeed);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 100);
      break;

    case 'J':   // Trás Direita
      Serial.println(state);
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 100);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, vSpeed);
      break;

    case 'B':   // Trás
      Serial.println(state);
      analogWrite(motorA1, 0);
      analogWrite(motorA2, vSpeed);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorB2, 0);
      break;

    case 'F':   // Frente
      Serial.println(state);
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, vSpeed);
      break;

    case 'S':   // Parado
    delay(100);
    Serial.println(state);
     analogWrite(motorA1, 0);
     analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
     analogWrite(motorB2, 0);
      break;

  }
}
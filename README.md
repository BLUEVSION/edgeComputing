# edgeComputing
Repositório destinado a Global Solution da matéria de Edge Computing

# Monitoramento de Qualidade da Água com Arduino

## Descrição

Este projeto tem como objetivo monitorar a qualidade da água utilizando sensores conectados a um Arduino. O sistema lê dados de temperatura, turbidez, CO2 (usando umidade como proxy), e pH, exibindo-os em um display LCD. Além disso, LEDs e um buzzer são usados para indicar a condição da água: condições ideais, alertas e perigos.Dessa forma conseguiremos monitorar as empresas que estão realizando suas operções no oceano e alertando-as se caso estiverem danificando o meio ambiente

## Sumário

- [Descrição](#descrição)
- [Componentes e Dependências](#componentes-e-dependências)
- [Esquemático de Montagem](#esquemático-de-montagem)
- [Configuração do Ambiente](#configuração-do-ambiente)
- [Instruções de Uso](#instruções-de-uso)
- [Licença](#licença)

## Componentes e Dependências

### Componentes

- Arduino Uno ou compatível
- Sensor de temperatura e umidade DHT22
- Sensor de turbidez analógico
- Sensor de pH analógico
- Potenciômetro (para simular o sensor de pH)
- Display LCD 20x4 com interface I2C
- LEDs (verde, amarelo e vermelho)
- Resistores (220 ohms para os LEDs)
- Buzzer piezoelétrico
- Protoboard e jumpers

### Dependências

- Biblioteca `LiquidCrystal_I2C` para controle do LCD
- Biblioteca `DHT` para leitura do sensor de temperatura e umidade

As bibliotecas podem ser instaladas através do gerenciador de bibliotecas da Arduino IDE.

## Esquemático de Montagem

**Conexões dos componentes:**

- **DHT22**
  - VCC -> 5V
  - GND -> GND
  - DATA -> Pino 9

- **Sensor de Turbidez**
  - VCC -> 5V
  - GND -> GND
  - OUT -> Pino A0

- **Sensor de pH**
  - VCC -> 5V
  - GND -> GND
  - OUT -> Pino A1

- **Potenciômetro**
  - VCC -> 5V
  - GND -> GND
  - OUT -> Pino A2

- **LCD 20x4 I2C**
  - SDA -> SDA
  - SCL -> SCL

- **LEDs e Buzzer**
  - LED Verde: Pino 13 (com resistor de 220 ohms)
  - LED Amarelo: Pino 12 (com resistor de 220 ohms)
  - LED Vermelho: Pino 11 (com resistor de 220 ohms)
  - Buzzer: Pino 10

## Configuração do Ambiente

1. **Instalar Arduino IDE**
   - Baixe e instale a [Arduino IDE](https://www.arduino.cc/en/software).

2. **Instalar Bibliotecas**
   - Abra a Arduino IDE e vá em: `Sketch -> Incluir Biblioteca -> Gerenciar Bibliotecas`
   - Procure por `LiquidCrystal_I2C` e instale.
   - Procure por `DHT sensor library` e instale.

## Instruções de Uso

1. **Montar o circuito** conforme o esquemático de montagem acima.
2. **Carregar o código no Arduino**:
   - Abra a Arduino IDE.
   - Copie e cole o código abaixo na IDE.
   - Conecte seu Arduino ao computador.
   - Selecione a porta correta e o tipo de placa na IDE.
   - Clique em `Upload`.
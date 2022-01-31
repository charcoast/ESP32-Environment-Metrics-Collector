# ESP32-Environment-Metrics-Collector

* Objetivos:<br/>
Código que faça leitura de sensores, calcule os dados e envie para uma API que fará a inserção no banco de dados.

* Sensores:<br/>
Temperatura, umidade do solo e luminosidade

* Como os dados são enviados:<br/>
Por meio do wifi, e com requisições em um servidor usando HTTPS

* Problemas encontrados
1. Arduino IDE e outras plataformas, como o PlatformIO não conseguem escrever o código no ESP<br/>
**Descrição**: Ao tentar escrever o código apresenta mensagem de erro.<br/>
**Solução/Paliativa**: Soldar um capacitor de 10uF em uns [pinos](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/02/fix-timed-out-waiting-for-packet-header-capacitor_f.jpg?w=750&ssl=1) (solução meio porca no meu ver) ou pressionar e segurar o botão de boot enquanto a ferramenta de upload está tentando se conectar na porta de comunicação serial.<br/>
**Infelizmente**: Parece uma questão de hardware que não será resolvida.

2. Não conecta no Wifi<br/>
**Descrição**: Carregado o código para dentro do ESP32, mesmo com as credenciais corretas, ocorre erro de conexão à rede wireless.<br/>
**Paliativas**: Reiniciar o ESP após o upload do código pressionando o botão EN, ou chamar a função <code>WiFi.disconnect();</code> já no setup (nem sempre funciona).<br/>
**Infelizmente**: Não encontrei solução até o momento.

3. Pinos GPIO ADC2_X não liam os dados do sensor<br/>
**Descrião**: Mesmo que nada estivesse conectado à porta, o analogRead() retornava sempre o valor máximo (4095), como se estivesse em curto com o 3v3. Garimpando na internet descobri que existe algumas issues no repositório da Espressif no Github. Ocorre que há um bug na lib Wifi que modifica os registradores dos pinos ADC2_X, tornando-os itutilizáveis durante o uso do Wifi (Pelo que li também ocorre habilitando o Bluetooth).<br/>
**Solução**: Algum hacker de hardware [descobriu](https://github.com/espressif/arduino-esp32/issues/102#issuecomment-559566728) que se [salvar o estado do registrador](https://github.com/charcoast/ESP32-Environment-Metrics-Collector/blob/master/src/main.cpp#L75) antes de iniciar o Wifi e, imediatamente antes de realizar uma leitura analógica esse registrador ser [resetado](https://github.com/charcoast/ESP32-Environment-Metrics-Collector/blob/master/src/main.cpp#L123) para o valor original, é possível fazer a leitura corretamente. Outro hacker de hardware [descobriu](https://github.com/espressif/arduino-esp32/issues/102#issuecomment-593650746) uma forma de [corrigir uma inversão dos valores lidos](https://github.com/charcoast/ESP32-Environment-Metrics-Collector/blob/master/src/main.cpp#L124) que ocorriam em alguns casos nessas portas e apresentou para a comunidade.<br/>
**Infelizmente**: Até o momento o problema não foi corrigido.

4. Método POST falha pois o servidor não entendeu a requisição<br/>
**Descrião**: O servidor HTTP recebia o POST, mas respondia com BAD REQUEST.<br/>
**Solução**: Utilizei a biblioteca [<code>#include <ArduinoJson.h></code>](https://arduinojson.org/) para [serializar](https://github.com/charcoast/ESP32-Environment-Metrics-Collector/blob/master/src/main.cpp#L174) os dados em JSON e enviá-los para o [servidor](https://github.com/charcoast/storage-sensor-data)<br/>
**Dica**: Verifique o [assistente](https://arduinojson.org/v6/assistant/) do ArduinoJson se pretende utilizá-lo, ajuda muito.
 
5. Código só roda quando o serial monitor está escutando<br/>
**Descrião**: Percebi que o código não é executado no ESP até que o monitor serial seja aberto naquela porta.<br/>
**Solução**: Sem solução<br/>
**Infelizmente**: Parece um problema no circuito de reinício do ESP32. A [issue](https://github.com/espressif/esp-idf/issues/59) que tratava desse problema foi encerrada, mas fiz um [comentário](https://github.com/espressif/esp-idf/issues/59#issuecomment-646764326).

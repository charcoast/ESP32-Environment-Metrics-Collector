# ESP32-Environment-Metrics-Collector

* Objetivos:<br/>
Código que faça leitura de sensores, calcule os dados e envie para uma API que fará a inserção no banco de dados.

*Sensores:<br/>
Temperatura, umidade do solo e luminosidade

*Como os dados são enviados:<br/>
Por meio do wifi, e com requisições em um servidor usando HTTPS

* Problemas encontrados
1. Arduino IDE e outras plataformas, como o PlatformIO não conseguem escrever o código no ESP<br/>
**Descrição**: Ao tentar escrever o código apresenta mensagem de erro.
**Solução/Paleativa**: Soldar um capacitor de 2.2uF em uns pinos lá(solução meio porca no meu ver) ou pressionar e segurar o botão de boot enquanto a ferramenta de upload está tentando se conectar na porta de comunicação serial.<br/>
**Infelizmente**: Parece uma questão de hardware que não será resolvida.

2. Não conecta no Wifi<br/>
**Descrição**: Carregado o código para dentro do ESP32, mesmo com as credenciais corretas, ocorre erro de conexão à rede wireless.<br/>
**Paleativas**: Reiniciar o ESP após o upload do código pressionando o botão EN, ou chamar a função <code>WiFi.disconnect();</code> já no setup (nem sempre funciona).
**Infelizmente**: Não encontrei solução até o momento.

3. Leitura dos pinos GPIO ADC2_X não liam os dados do sensor<br/>
**Descrião**: Mesmo que nada estivesse conectado à porta, o analogRead() retornava sempre o valor máximo (4095), como se estivesse em curto com o 3v3. Garimpando na internet descobri que existe algumas issues no repositório da Espressif no Github. Ocorre que há um bug na lib Wifi que modifica os registradores dos pinos ADC2_X, tornando-os itutilizáveis durante o uso do Wifi (Pelo que li também ocorre habilitando o Bluetooth).<br/>
**Solução**: Algum hacker de hardware descobriu que se salvar o estado do registrador antes de iniciar o Wifi e, imediatamente antes de realizar uma leitura analógica esse registrador ser resetado para o valor original, é possível fazer a leitura corretamente. Outro hacker de hardware descobriu uma forma de corrigir uma inversão dos valores lidos que ocorriam em alguns casos nessas portas e apresentou para a comunidade.<br/>
**Infelizmente**: Até o momento não foi corrigido o problema

4. Método POST falha pois o servidor não entendeu a requisição<br/>
**Descrião**: O servidor HTTP recebia o POST, mas respondia com BAD REQUEST.<br/>
**Solução**: Utilizei a biblioteca <code>#include <ArduinoJson.h></code> para serializar os dados em JSON e enviá-los para o servidor
<br/>
  
5. Código só roda quando o serial monitor está escutando<br/>
**Descrião**: Percebi que o código não é executado no ESP até que o monitor serial seja aberto naquela porta.<br/>
**Solução**: Sem solução<br/>
**Infelizmente**: Parece um problema no circuito de reinício do ESP32. A issue que tratava desse problema foi encerrada, mas dei uma cutucada para ver se eles acordam.

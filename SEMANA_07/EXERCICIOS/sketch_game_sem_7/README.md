# Pedra, papel e tesoura

## Funcionamento 
A página HTML contém botões para os dois jogadores escolherem entre três opções para ganhar o jogo. Cada botão contém um link pela tag ```<a>``` que leva para diferentes endereços para requisições GET. A partir daí, o servidor embarcado vê o endereço de cada requisição e coloca as opções (pedra, papel ou tesoura) dos dois jogadores em variáveis para montar a lógica do jogo.
___

## Resposta na plaquinha

No projeto, a ESP32 tem conexões separadas entre player 1 e player 2, sendo que cada um dos jogadores tem um led verde e outro vermelho para dar feedbacks do resultado do jogo:

<a href="https://youtu.be/qZq0copdf04"><img src="https://cdn.icon-icons.com/icons2/640/PNG/512/youtube-video-social-media-play_icon-icons.com_59108.png" height="20px">   Vídeo de exemplo de funcionamento</a>

<img height="500px" src="https://github.com/ThomeGiovana/modulo_4/blob/main/SEMANA_07/EXERCICIOS/sketch_game_sem_7/circuito.jpg?raw=true" >

Existem três possíveis resultados, a vitória do player 1, vitória do player 2 e empate (vitória do player 0). Os componentes de hardware darão resposta da seguinte maneira:

<u>Vitória do player 1:</u>

```ledP1verde``` on, <br> ```ledP2vermelho``` on

<u>Vitória do player 2:</u>

```ledP2verde``` on, <br> ```ledP1vermelho``` on

<u>Vitória do player 0 (empate):</u>

```ledP1vermelho``` on,<br>
```ledP2vermelho``` on,<br>
```ledP1verde``` on,<br>
```ledP2verde``` on,

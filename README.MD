# Introdução

Esse repositorio foi criado para quem deseja reproduzir o projeto de volante do porsche 992 hospedado nesse !(link)https://www.printables.com/model/337684-turn-911-gt3-r-2023-diy-sim-racing-steering-wheel, ao criar esse volante algumas coisas não estavam 100% presentes e também o link do discord para tirar duvidas parece que foi desativado, outra dificuldade foi não ir pelo caminho de mandar fazer a PCB, o que iria encaresser demais o valor do volante, que no momento que fiz gastei em torno de R$500,00. Para esse projeto é necessario uma impressora 3d e algumas ferramentas que vou listar aqui, então antes de decidir reproduzir esse volante verifique se consiga ter acesso a ferramentas e componentes que serão necessários.

Esse foi o primeiro volante que fiz e também primeiro contato com muita das coisas que precisei fazer como pintura, eletronica, arduino, etc, Logo você pode identificar algumas decisões erradas empregadas aqui, se tiver algo a acrescentar faça um comentario ou issue ou PR, se tiver familiarizado com o GitHUB.

Diferenças entre o projeto original e o que acabei fazendo, no lugar dos rotacionadores centrais que possuem posições especificas eu optei por utilizar encoders rotativos comuns o que faz reduzir as opções de configurações, mas o volante acabou ficando com 26 botões, acredito que seja o suficiente para configurar tudo durante a corrida. Volante não possui quaisquer LED, prefiri dar prioridade aos botões.

# Caracteristicas do volante

2 - Paddle Switchs
1 - Embreagem (potenciomento)
14 - Botões (12 Frontais e 2 Traseiros)
5 - Encoders rotativos 
1 - Joystick Analogico

# Materiais

 - Fusion360
    - Licença para uso pessoal.
- Impressora 3d 
 - Utilizei uma Ender 3 V1 com bico de 0.4 e 1Kg de filamento de qualquer cor eu utilizei PLA
 - Uma chapa de aluminio de 3mm 20x30cm
    - Serra tico-tico
    - Laminas para aluminio que cortem aluminio de 3m possam fazer contorno.
    - Sugestão de serras: Bosh T118EOF ou Starrett BU214S
- Lixas (150,250, 400 e 600)
- Spray 
    - Primer
    - Preto
    - Cinza Metalico
    - Verniz
- Parafusos e Porcas
  - M3
  - M4
- Switchs
- Insert metalico de rosca
    - M3
    - M4
- Botões
    - Tactil de 12mm
- Arduino Pro micro
- Imã
    - 10x3mm
- Encoders Rotativos
- Potenciomento 10k
- Multiplexador 16 canais CD74HC4067
- Cabos Jumpers para prototipo e euilização posterior.
- Ferro de Solda
- Estanho
- Joystick Analogico para arduino
- Cabo USB micro espiral
- Plugue macho e femea GX2 de 4 vias
- Multimetro

# Impressão 3d

Não tem muito segredo para a impressão 3d, a orientação das peças estão presentes no PDF dentro desse repositorio, unica dica é referente a altura da camada, se o seu fatiador possuir a funcionalidade de altura variavel, reduza a altura da camada em lugares curvos para reduzir o tempo de lixamento, é melhor a impressora trabalhar do que você!.

# Aro em ALuminio (Opicional)

# Lixamento e Pintura

# Soldagem

# Eletronica

# Embreagem

No projeto não da detalhes de como fazer a embreagem, então recorri a um pojeto de embreagem pronto e adaptei ao furo do volante, os arquivos podem ser encontrados nesse repositorio

# Joystick Analogico

# Knobs

Os knobs utilizados nesse projeto originalmente achei pequenos e acabei optando por fazer novos utilizando esse projeto: !(link)https://www.printables.com/model/580299-ultimate-diy-replacement-knob-pack-for-samsung-sme/files
Acabei utilizando o modelo 7, para editar ele de acordo com as dimensões do furo você vai precisar do Fusion360, nesse !(video)https://www.youtube.com/watch?v=VST1j0NKjeQ ele mostra como, nele vc consegue dimensionar para caber nos furos da tampa do volante.
# Montagem

# Grips (empunhaduras)



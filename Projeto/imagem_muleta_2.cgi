#!/bin/bash

ARQUIVODADOS=/home/pi/ESZB026-17-6-2024C/Projeto/muleta_dados.txt
echo "Content-type: text/html"
echo ""
echo '<HTML><HEAD><meta charset="UTF-8">'
echo '<TITLE>Figura do gráfico montado com os dados da Ponte de Wheatstone</TITLE></HEAD>'
echo '<BODY style="background-color:#FFFFE0"><H1>Dados fornecidos pela porta A0 do arduíno</H1>'
echo 'Estou no diretório '
pwd
echo ', logado como o usuário '
whoami
echo '.<br>'
echo '<h2>DADOS:</h2>'
echo '<pre>'
cat $ARQUIVODADOS
echo '</pre>'
echo '<br>'
echo '<br>'
echo '<h2>IMAGENS:</h2>'
echo 'Referenciando a imagem como "/cgi-bin/muleta_imagem.cgi":<br>'
echo '<img src="/cgi-bin/muleta_imagem.cgi">'
echo '<br>'
echo 'Referenciando a imagem como "muleta_imagem.cgi":<br>'
echo '<img src="muleta_imagem.cgi">'
echo '<br>'
echo '</HTML>'

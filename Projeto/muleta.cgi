echo "Content-type: text/html"
echo ""
echo '<html><head><meta charset="UTF-8">'
echo '<title>Leitura de dados com Arduino</title></head>'
echo '<body style="background-color:#F0F8FF; text-align:center;">'
echo '<h1>Coletando dados da muleta usando uma Ponte de Wheatstone no Arduino via SPI.</h1>'
echo '<p>Dados coletados na porta A0 do Arduino a 1.000 amostras / segundo.</p>'
echo '<p>Rodando programa le_muleta. Saída apresentada:</p>'
/usr/local/bin/muletaterminal

echo '<h2>Imagem:</h2>'
echo '<img src="muleta_imagem.cgi" style="margin:auto; display:block;">'
echo '</body></html>'

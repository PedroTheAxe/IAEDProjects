<html>
<body>
<h3> Insira as coordenadas de um ponto e as variacoes em X e Y:</h3>
<form action = "list_anomalias.php" method ="post">
<p>X: <input type="number" name="x" min="-90" max="90" step=".000001" required/><p>
<p>Y: <input type="number" name="y" min="-180" max="180" step=".000001" required/><p>
<p>dX: <input type="number" name="dx" min="0" max="90" step=".000001" required/><p>
<p>dY: <input type="number" name="dy" min="0" max="180" step=".000001" required/><p>
<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"homepage.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>
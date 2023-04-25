<html>
<body>
<h3> Insira um novo item neste local: <?=$_GET['nome']?></h3>
<form action = "validation_item.php" method ="post">
<p><input type="hidden" name="nome"
value="<?=$_GET['nome']?>"/></p>
<p><input type="hidden" name="lat"
value="<?=$_GET['lat']?>"/></p>
<p><input type="hidden" name="lon"
value="<?=$_GET['lon']?>"/></p>
<p>Descricao do item: <input type="text" name="descricao_item" required/><p>
<p>Localizacao: <input type="text" name="localizacao" required/><p>
<p>Zona: <input type="text" name="zona" required/><p>
<p>Imagem: <input type="text" name="imagem" required/><p>
<p>Lingua: <input type="text" name="lingua" required/><p>
<p>Descricao da anomalia: <input type="text" name="descricao_anomalia" required/><p>
<p>Email: <input type="email" name="email" required/><p>
<p> Tipo de Anomalia:</p> 
    <input type="radio" name="anomaliaredacao" value="true"/>Redacao
    <input type="radio" name="anomaliaredacao" value="false"/>Traducao

<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"local.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>
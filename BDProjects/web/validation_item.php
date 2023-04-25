<html>
<body>
<?php
if (!empty($_POST["anomaliaredacao"])){
    if($_POST["anomaliaredacao"] == "true"){
        ?>
        <form name="myform" action = "insert_item.php" method ="post">
        <p><input type="hidden" name="nome"
        value="<?=$_POST["nome"]?>"/></p>

        <p><input type="hidden" name="lat"
        value="<?=$_POST["lat"]?>"/></p>

        <p><input type="hidden" name="lon"
        value="<?=$_POST["lon"]?>"/></p>
        
        <p><input type="hidden" name="descricao_item"
        value="<?=$_POST["descricao_item"]?>"/></p>

        <p><input type="hidden" name="localizacao"
        value="<?=$_POST["localizacao"]?>"/></p>

        <p><input type="hidden" name="zona"
        value="<?=$_POST["zona"]?>"/></p>
        
        <p><input type="hidden" name="imagem"
        value="<?=$_POST["imagem"]?>"/></p>
        
        <p><input type="hidden" name="lingua"
        value="<?=$_POST["lingua"]?>"/></p>
        
        <p><input type="hidden" name="descricao_anomalia"
        value="<?=$_POST["descricao_anomalia"]?>"/></p>

        <p><input type="hidden" name="email"
        value="<?=$_POST["email"]?>"/></p>
        
        <p><input type="hidden" name="anomaliaredacao"
        value="<?=$_POST["anomaliaredacao"]?>"/></p>
        </form>
        <script type="text/javascript">
            document.myform.submit();
        </script>
        <?php
    }
    else{
        ?>
        <form action = "insert_item.php" method ="post">
        <p><input type="hidden" name="nome"
        value="<?=$_POST["nome"]?>"/></p>

        <p><input type="hidden" name="lat"
        value="<?=$_POST["lat"]?>"/></p>

        <p><input type="hidden" name="lon"
        value="<?=$_POST["lon"]?>"/></p>

        <p><input type="hidden" name="descricao_item"
        value="<?=$_POST["descricao_item"]?>"/></p>

        <p><input type="hidden" name="localizacao"
        value="<?=$_POST["localizacao"]?>"/></p>
        
        <p><input type="hidden" name="zona"
        value="<?=$_POST["zona"]?>"/></p>
        
        <p><input type="hidden" name="imagem"
        value="<?=$_POST["imagem"]?>"/></p>
        
        <p><input type="hidden" name="lingua"
        value="<?=$_POST["lingua"]?>"/></p>
        
        <p><input type="hidden" name="descricao_anomalia"
        value="<?=$_POST["descricao_anomalia"]?>"/></p>

        <p><input type="hidden" name="email"
        value="<?=$_POST["email"]?>"/></p>
        
        <p><input type="hidden" name="anomaliaredacao"
        value="<?=$_POST["anomaliaredacao"]?>"/></p>

        <p>Zona2: <input type="text" name="zona2"/><p>

        <p>Lingua2: <input type="text" name="lingua2"/><p>

        <p><input type="submit" name="submit" value="Submit"/></p>
        </form>
        <?php
    }
}
?>
</body>
</html>
<html>
<body>
<?php

$host = "db.ist.utl.pt";
$user = "ist193607";
$port = 5432;
$password = "1234";
$dbname = $user;
$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$aid=$_POST['aid'];
$texto=$_POST['texto'];
$email=$_POST['email'];

$date= new DateTime();
$ts = $date->format('Y-m-d H:i:s') . "\n";
$data_hora = $ts ;

//Validacao dos dados inseridos pelo user no formulario
$valid = true;
if(strpos($email,'@') === false){
    $valid = false;
}

if($valid == true){

    $query1 = "SELECT * FROM utilizador WHERE email = '$email';";
    $result1 = pg_query($query1) or die('ERROR: '.pg_last_error());
    if(pg_num_rows($result1)== 0){
        $str=uniqid();
        $passwd= $str;
        $sql = "SELECT utilizador_qualificado_insert($1,$2);";
        $result = pg_prepare($connection,"my_query3",$sql);
        $result = pg_execute($connection,"my_query3",array($email,$passwd));
       
   
    }

    $sql = "SELECT max(nro) FROM proposta_de_correcao;";
    $result = pg_query($sql) or die('ERROR: '.pg_last_error());
    $nro_maxcount=pg_fetch_result($result,0,0)+1;
    


    $sql = "INSERT INTO proposta_de_correcao VALUES($1,$2,$3,$4);";
    $result = pg_prepare($connection,"my_query",$sql);
    $result = pg_execute($connection,"my_query",array($email,$nro_maxcount,$data_hora,$texto));


    $sql = "INSERT INTO correcao VALUES($1,$2,$3);";
    $result = pg_prepare($connection,"my_query2",$sql);
    $result = pg_execute($connection,"my_query2",array($email,$nro_maxcount,$aid));

    
    $result = pg_free_result($result) or die('ERROR:' . pg_last_error());
    echo("<p> Proposta registada com sucesso</p>");
}

pg_close($connection);
if($valid == false){
    echo("<p> A proposta nao foi registada</p>");
}
echo("<p><a
href=\"correction.php\">Voltar a pagina anterior </a></p>\n");

?>
</body>
</html>
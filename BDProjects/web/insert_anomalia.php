<html>
<body>
<?php

$host = "db.ist.utl.pt";
$user = "ist193607";
$port = 5432;
$password = "jtck9665";
$dbname = $user;
$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$id=$_POST['id'];
$zona=$_POST['zona'];//todo
$imagem= $_POST['imagem'];//todo
$lingua=$_POST['lingua'];
$descricao= $_POST['descricao'];
$email=$_POST['email'];//todo
$anomaliaredacao= $_POST['anomaliaredacao'];
$date= new DateTime();
$ts = $date->format('Y-m-d H:i:s') . "\n";
$timestamp = $ts ;

//Validacao dos dados inseridos pelo user no formulario
$valid = true;
$arrayzona = explode(',',$zona);
if(count($arrayzona)==4){
    for($i=0;$i<count($arrayzona);$i++){
        if(!(preg_match("/^\d+$/", $arrayzona[$i])) || !(strlen($arrayzona[$i])==3)){
            $valid = false;
            break;
        }
    }
}else{
    $valid = false;
}

if($anomaliaredacao == 'false'){
    $zona2=$_POST['zona2'];
    $lingua2=$_POST['lingua2'];
    $arrayzona2 = explode(',',$zona2);
    if(count($arrayzona2)==4){
        for($i=0;$i<count($arrayzona2);$i++){
            if(!(preg_match("/^\d+$/", $arrayzona2[$i])) || !(strlen($arrayzona2[$i])==3)){
                $valid = false;
                break;
            }
        }
    }else{
        $valid = false;
    }
}

if(strpos($email,'@') === false){
    $valid = false;
}

if(strpos($imagem,'.jpeg') === false){
    $valid = false;
}

if($anomaliaredacao == 'false'){
    if(strcmp($lingua,$lingua2)==0){
        $valid = false;
    }
}

if($anomaliaredacao == 'false'){
    if(((float)$arrayzona2[0] < (float)$arrayzona[2] && (float)$arrayzona2[2] > (float)$arrayzona[2]) || ((float)$arrayzona2 > (float)$arrayzona[0] && (float)$arrayzona2[0] < (float)$arrayzona[0]) || ((float)$arrayzona2[1] < (float)$arrayzona[3] && (float)$arrayzona2[3] > (float)$arrayzona[3]) || ((float)$arrayzona2[3] > (float)$arrayzona[1] && (float)$arrayzona2[1] < (float)$arrayzona[1])){
        $valid = false;
    }
}


if($valid == true){
    $sql = "SELECT max(id) FROM anomalia;";
    $result = pg_query($sql) or die('ERROR: '.pg_last_error());

    $a_maxcount=pg_fetch_result($result,0,0)+1;

    $query1 = "SELECT * FROM utilizador WHERE email = '$email';";
    $result1 = pg_query($query1) or die('ERROR: '.pg_last_error());

    $sql = "INSERT INTO anomalia VALUES($1,$2,$3,$4,$5,$6,$7);";
    $result = pg_prepare($connection,"my_query",$sql);
    $result = pg_execute($connection,"my_query",array($a_maxcount,$zona,$imagem,$lingua,$timestamp,$descricao,$anomaliaredacao));

    if(pg_num_rows($result1)== 0){
        $str=uniqid();
        $passwd= $str;
        $sql = "SELECT utilizador_regular_insert($1,$2);";
        $result = pg_prepare($connection,"my_query2",$sql);
        $result = pg_execute($connection,"my_query2",array($email,$passwd));
    }


    $sql = "INSERT INTO incidencia VALUES($1,$2,$3);";
    $result = pg_prepare($connection,"my_query3",$sql);
    $result = pg_execute($connection,"my_query3",array($a_maxcount,$id,$email));



    if($anomaliaredacao == 'false'){
   
        $sql= "INSERT INTO anomalia_traducao VALUES($1,$2,$3);";
        $result = pg_prepare($connection,"my_query4",$sql);
        $result = pg_execute($connection,"my_query4",array($a_maxcount,$zona2,$lingua2));
    
    }
    $result = pg_free_result($result) or die('ERROR:' . pg_last_error());
    echo("<p> Anomalia inserida com sucesso</p>");
}

pg_close($connection);
if($valid == false){
    echo("<p> Anomalia inserida sem sucesso</p>");
}
echo("<p><a
href=\"local.php\">Voltar a pagina anterior </a></p>\n");

?>
</body>
</html>
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

$nome=$_POST['nome'];
$lat=$_POST['lat'];
$lon=$_POST['lon'];
$descricao_item= $_POST['descricao_item'];
$localizacao= $_POST['localizacao'];
$zona=$_POST['zona'];
$imagem= $_POST['imagem'];
$lingua=$_POST['lingua'];
$descricao_anomalia= $_POST['descricao_anomalia'];
$email=$_POST['email'];
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

if(!(-90<=$lat && $lat<=90) || !(-180<=$lon && $lon<=180)){
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
    //Obter IDs seguintes
    $sql = "SELECT max(id) FROM anomalia;";
    $result = pg_query($sql) or die('ERROR: '.pg_last_error());
    $a_maxcount=pg_fetch_result($result,0,0)+1;
    

    $sql = "SELECT max(id) FROM item;";
    $result = pg_query($sql) or die('ERROR: '.pg_last_error());
    $i_maxcount=pg_fetch_result($result,0,0)+1;
    
    

    //Inserir nas tabelas com Protecao de SQL Injection
    $query1 = "SELECT * FROM utilizador WHERE email = '$email';";
    $result1 = pg_query($query1) or die('ERROR: '.pg_last_error());
   

    $sql = "INSERT INTO local_publico VALUES($1,$2,$3);";
    $result = pg_prepare($connection,"my_query1",$sql);
    $result = pg_execute($connection,"my_query1",array($lat,$lon,$nome));
    

    $sql = "INSERT INTO anomalia VALUES($1,$2,$3,$4,$5,$6,$7);";
    $result = pg_prepare($connection,"my_query2",$sql);
    $result = pg_execute($connection,"my_query2",array($a_maxcount,$zona,$imagem,$lingua,$timestamp,$descricao_anomalia,$anomaliaredacao));
    

    if(pg_num_rows($result1)== 0){
        $str=uniqid();
        $passwd= $str;
        $sql = "SELECT utilizador_regular_insert($1,$2);";
        $result = pg_prepare($connection,"my_query3",$sql);
        $result = pg_execute($connection,"my_query3",array($email,$passwd));
        
    }

    $sql = "INSERT INTO item VALUES($1,$2,$3,$4,$5);";
    $result = pg_prepare($connection,"my_query4",$sql);
    $result = pg_execute($connection,"my_query4",array($i_maxcount,$descricao_item,$localizacao,$lat,$lon)); 
    


    $sql = "INSERT INTO incidencia VALUES($1,$2,$3);";
    $result = pg_prepare($connection,"my_query5",$sql);
    $result = pg_execute($connection,"my_query5",array($a_maxcount,$i_maxcount,$email));
    



    if($anomaliaredacao == 'false'){
   
        $sql= "INSERT INTO anomalia_traducao VALUES($1,$2,$3);";
        $result = pg_prepare($connection,"my_query6",$sql);
        $result = pg_execute($connection,"my_query6",array($a_maxcount,$zona2,$lingua2));
    
    }
    $result = pg_free_result($result) or die('ERROR:' . pg_last_error());
    echo("<p> Incidencia inserida com sucesso</p>");
}

pg_close($connection);
if($valid == false){
    echo("<p> Incidencia inserida sem sucesso</p>");
}
echo("<p><a
href=\"local.php\">Voltar a pagina anterior </a></p>\n");

?>
</body>
</html>
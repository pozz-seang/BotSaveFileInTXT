<?php

if(isset($_POST['battery'])){
    $myfile = fopen("file/battery.txt", "w") or die("Unable to open file!");
    fwrite($myfile, $_POST['battery']);
    fclose($myfile);
}

    
?>
<?php
    include "botToken.php";

    echo 'SEHacker_bot';

    $update = file_get_contents('php://input');
    $update = json_decode($update, true);

    if(isset($_POST['userChatId'])){
        $userChatId = $_POST['userChatId'];
    }else{
        //user ID
        $userChatId = $update["message"]["from"]["id"]?$update["message"]["from"]["id"]:null;
    }



    if($userChatId){
    //message
    $userMessage = $update["message"]["text"]?$update["message"]["text"]:"Nothing";
    //name
    $firstName = $update["message"]["from"]["first_name"]?$update["message"]["from"]["first_name"]:null;
    $lastName = $update["message"]["from"]["last_name"]?$update["message"]["from"]["last_name"]:null;
    $fullName = $firstName." ".$lastName;
        //$replyMsg = "Hello ".$fullName."\nYou said: ".$userMessage;
    
        if($userMessage=='/start'){
            $replyMsg = "Hey [".$fullName."](tg://user?id=".$userChatId.")!\nWellcome to @SEHacker\_Bot.\nHow can i help You?";
        }else if($userMessage=='/battery'){
            $myfile = fopen("file/battery.txt", "r") or die("Unable to open file!");
            $replyMsg = fread($myfile,filesize("file/battery.txt"));
            fclose($myfile);
        }


        
        send("sendMessage", [
            "chat_id" => $userChatId,
            "text" => $replyMsg,
            "parse_mode" => "markdown"
        ]);
    
    
    }
    
    function send($method, $data){
        global $BOT_TOKEN;
        $url = "https://api.telegram.org/bot$BOT_TOKEN/$method";
    
        if(!$curld = curl_init()){
            exit;
        }
        curl_setopt($curld, CURLOPT_POST, true);
        curl_setopt($curld, CURLOPT_POSTFIELDS, $data);
        curl_setopt($curld, CURLOPT_URL, $url);
        curl_setopt($curld, CURLOPT_RETURNTRANSFER, true);
        $output = curl_exec($curld);
        curl_close($curld);
        return $output;
    }
    
?>
    
<?php
// configuration
require("../includes/config.php");
// if form was submitted
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
        // TODO
        if (empty($_POST["username"])||empty($_POST["password"]))
        {
            apologize("Missing Fields.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password doesn't match.");
        }
        
        if (query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"])) === false)
        {
            apologize("Username not available.");
            
        }
        
        else
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("index.php");
        }
        
        
}  
else
{
    // else render form
    render("register_form.php", ["title" => "Register"]);
}
?>

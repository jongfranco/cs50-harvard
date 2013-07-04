<?php

    // configuration
    require("../includes/config.php"); 

    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        // detect positive whole number for deposit
        if (preg_match("/^\d+$/", $_POST["deposit"]) == false)
        {
            apologize("You must enter a whole, positive integer.");
        }
        
        // update user's cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["deposit"], $_SESSION["id"]);
        
        // redirect to portfolio 
        redirect("/");
    }
    
    else
    {
        // render deposit_form
        render("deposit_form.php", ["title" => "Deposit Form"]);
    }

?>

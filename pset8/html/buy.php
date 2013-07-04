<?php
    
    // configuration 
    require("../includes/config.php");   
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
  	//look for missing fields
        if (empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("Missing fields.");
        }
        //look for invalid symbols
        if (lookup($_POST["symbol"]) === false)
        {
            apologize("Invalid stock symbol.");
        }
        
        // detect positive whole number
        if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid input. Must be a positive whole number.");
        }
        //transaction process
        $transaction = 'BUY';
        
        $stock = lookup($_POST["symbol"]);
        $cost = $stock["price"] * $_POST["shares"];
        
        $cash =	query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);	
        //check cash
        if ($cash < $cost)
        {
            
            apologize("Insufficient cash.");
        }         
        
        else
        {
         
            $_POST["symbol"] = strtoupper($_POST["symbol"]);
                         
            // insert values to buyers
            query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) 
                ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            s
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
            
            // update history
            query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $stock["price"]);

            //redirect to portfolio
            redirect("/");    
        }
    }
    
    // if form hasn't been submitted
    else
    {
     // render buy form
        render("buy_form.php", ["title" => "Buy Form"]);
    }
    
?>

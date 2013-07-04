<?php

    // configuration
    require("../includes/config.php");  
    
    // if form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") 
    {
        //transaction
        $transaction = 'SELL';
        $stock = lookup($_POST["symbol"]);
        
        // query for shares
        $shares = query("SELECT shares FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // process values
        $value = $stock["price"] * $shares[0]["shares"];
        
        // query for updating user's cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $value, $_SESSION["id"]);

        // delete stocks 
        query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);        
        
        // update history
        query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], $transaction, $_POST["symbol"], $shares[0]["shares"], $stock["price"]);

        // redirect to portfolio 
        redirect("/");
    }
    
    // if form hasn't been submitted
    else
    {
        // query user's portfolio
        $rows =	query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);	

        $stocks = [];

        foreach ($rows as $row)	
        {   
            $stock = $row["symbol"];
            $stocks[] = $stock;       
        }    

        // render sell form
        render("sell_form.php", ["title" => "Sell Form", "stocks" => $stocks]);
    }
      

?>

<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // look for invalid symbols
        $_POST = lookup($_POST["symbol"]);

        if ($_POST === false)
        {
            apologize("Invalid stock symbol");
        }
        
        // render quote_price
        render("quote_price.php", ["title" => "Quote"]);

    }
    else
    {
        // render quote_form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>

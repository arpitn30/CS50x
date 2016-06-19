<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {    
        // display the quote form
        render("quote_form.php", ["title" => "Quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Lookup Stock
        $stock = lookup($_POST["symbol"]);
        if($stock == false)
        {
            apologize("Invalid Stock Symbol.");
        }
        render("quote.php",$stock);
    }
?>
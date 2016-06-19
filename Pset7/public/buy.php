<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // display the buy form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //Check for validity of shares
        if(!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares.");
        }
        
        //query database for the users balance
        $balance = CS50::query("SELECT cash FROM users WHERE id = ?",$_SESSION["id"]);
        
        //lookup stock
        $stock = lookup($_POST["symbol"]);
        if($stock == false)
        {
            apologize("Invalid Stock Symbol.");
        }
        
        if($balance[0]["cash"] < ($stock["price"] * $_POST["shares"]))
        {
            apologize("You can't afford that.");
        }
        
        //Change to uppercase
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        
        //Update table portfolios
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
        
        //Deduct from users balance
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?",($stock["price"] * $_POST["shares"]), $_SESSION["id"]);
        
        //add entry to history
        CS50::query("INSERT INTO history (uid, transaction, symbol, shares, price) VALUES(?, 'BUY', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
        
        //redirect to portfolio
        redirect("/");
    }
?>
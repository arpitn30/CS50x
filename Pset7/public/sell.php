<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {    
        //query database for the shares bought
        $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);

        // display the sell form
        render("sell_form.php", ["rows" => $rows, "title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //Lookup the price of stock
        $cost = lookup($_POST["symbol"]);
        
        //query for number of shares
        $stocks = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //Update table users
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?",($cost["price"] * $stocks[0]["shares"]), $_SESSION["id"]);
        
        //Update table portfolios
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //add entry to history
        CS50::query("INSERT INTO history (uid, transaction, symbol, shares, price) VALUES(?, 'SELL', ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $stocks[0]["shares"], $cost["price"]);
        
        // redirect to portfolio
        redirect("/");
    }
?>
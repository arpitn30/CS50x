<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("password_form.php", ["title" => "Password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        // validate submission
        if (empty($_POST["old"]))
        {
            apologize("You must enter your old password.");
        }
        else if (empty($_POST["new"]))
        {
            apologize("You must enter a new password.");
        }
        else if (($_POST["new"]) !== ($_POST["confirmation"]))
        {
            apologize("Your passwords do not match.");
        }
        
        //validate old password
        $password = CS50::query("SELECT hash FROM users WHERE id = ?",$_SESSION["id"]);
         if (!password_verify($_POST["old"], $password[0]["hash"]))
        {
            apologize("Please enter the correct password");
        }
        
        
        //query database to add user
        CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["new"], PASSWORD_DEFAULT), $_SESSION["id"]);
        
        // redirect to portfolio
        render("password.php",["title" => "Password"]);
    }

?>
<?php

    // configuration
    require("../includes/config.php");

    //query database for history
    $history = CS50::query("SELECT name, author, score, date_format(datetime, '%m/%d/%Y %l:%i %p') datetime, action FROM history WHERE uid = ?",$_SESSION["id"]);

    // display the sell form
    render("history.php", ["rows" => $history, "title" => "History"]);

?>

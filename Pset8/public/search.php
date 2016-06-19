<?php

	require(__DIR__ . "/../includes/config.php");

	// numerically indexed array of places
	$places = [];

	// TODO: search database for places matching $_GET["geo"], store in $places
	
	// Seperate Entries
	$db = array_map('trim', explode(",", $_GET["geo"]));
	
	$count = count($db);
	if($db[$count - 1] == 'US')
		$count = $count - 1;
	
	$qry = "SELECT * FROM places WHERE ";
	// query
	for($i = 0; $i < $count; $i++)
	{
		if(is_numeric($db[$i]))
		{
			$qry = $qry."postal_code LIKE '".htmlspecialchars($db[$i])."%' ";
		}
		else
		{
			if($i != 0)
				$qry = $qry.' OR ';
			$qry = $qry.'(place_name  LIKE "' . htmlspecialchars($db[$i]) .'%" 
			OR admin_name1 LIKE "' . htmlspecialchars($db[$i]) .'%" 
			OR admin_code1 LIKE "'. htmlspecialchars($db[$i]) .'%")';
		}
	}
	$places = CS50::query($qry);
	
	// output places as JSON (pretty-printed for debugging convenience)
	header("Content-type: application/json");
	print(json_encode($places, JSON_PRETTY_PRINT));

?>
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <label for="symbol">Select the stock you want to sell: </label><br>
            <select class="form-control" name="symbol" autofocus>
                <option disabled selected value="">Stock Symbol</option>
                <?php
                    foreach ($rows as $row)
                    {
                        print("<option value={$row["symbol"]}>{$row["symbol"]}</option>");
                    }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Sell</button>
        </div>
    </fieldset>
</form>

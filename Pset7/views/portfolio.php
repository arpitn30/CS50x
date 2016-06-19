<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody align="left">
            <?php foreach ($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= $position["price"] ?></td>
                <td><?= ($position["price"]*$position["shares"]) ?></td>
            </tr>
            <?php endforeach ?>
            <tr>
                <td colspan="4">CASH</td>
                <td><?= htmlspecialchars(number_format($balance,2)) ?></td>
            </tr>
        </tbody>
    </table>
</div>

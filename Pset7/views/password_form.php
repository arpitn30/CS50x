<form action="password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="old" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Re-enter New Password" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                Change Password
            </button>
        </div>
    </fieldset>
</form>
<?php	
	session_save_path("YOUR PATH");
	session_cache_limiter(false);
	session_start();
	
	if ($_SESSION['login_error']) {		
		echo '<div class="result"><p class="login-error text-emphasis">Email/Password combination not found.</p></div>';
	}
?>
<form action="" method="post" class="form-login"> 
	<fieldset> 
		<div>
			<label for="email">Email</label>
			<input type="email" name="email" required />
		</div>
		<div>
			<label for="password">Password</label>
			<input type="password" name="password" required />
		</div>  
	</fieldset>
	<button type="submit" name="login" value="login">Login</button>          
  </form>
<form action="" method="post">    
	<button type="submit" name="step" value="form_register_teacher" class="btn-de-emphasis">Register</button>  
</form> 

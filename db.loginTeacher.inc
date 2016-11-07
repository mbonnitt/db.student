<?php	
	session_save_path("YOUR PATH");
	session_cache_limiter(false);
	session_start();
	
	if ($_POST ||
			$_SESSION['teacher_id']) {
		if (!$_SESSION['login_test']) {
			include_once('php/php.loginTest.inc');
		} 
	}
	else {
		include_once('php/form.loginTeacher.inc');
	}
?>

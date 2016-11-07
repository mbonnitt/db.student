<?php	
	session_save_path("YOUR PATH");
	session_cache_limiter(false);
	session_start();
	
	/* GET DATABASE */ 
	$db = Database::getInstance();
	$mysqli = $db->getConnection();
	
	$email  = sanitize($mysqli, $_POST['email']);
	$password  = mysqli_real_escape_string($mysqli, $_POST['password']);
	
	$query  = "SELECT * FROM teacher ";
	$query .= "JOIN teacher_log_in ";
	$query .= "WHERE ";	
	$query .= "email = '$email' ";	
	$query .= "AND password = '$password' ";
	$result = $mysqli->query($query);
	$teacher_login = mysqli_fetch_array($result);   
	mysqli_close($db);   
		
	if (isset($teacher_login)) {	
		$_SESSION['teacher_id'] = $teacher_login['teacher_id'];	
		$_SESSION['logged_in'] = TRUE;
		$_SESSION['initial'] = TRUE;
		$_SESSION['login_error'] = FALSE;
		header('Refresh: 0');
	}  
	else {	
		$_SESSION['login_error'] = TRUE;
		header('Refresh: 0');
	}

?>

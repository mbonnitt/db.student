<?php
	/* GET DATABASE */ 
	$db = Database::getInstance();
	$mysqli = $db->getConnection();
	
	/* VARIABLES */
	// personal info 
	$teacher_id 	= sanitize($mysqli, $_POST['teacher_id']);
	$first_name 	= sanitize($mysqli, $_POST['first_name']);
	$last_name 		= sanitize($mysqli, $_POST['last_name']);
	$email		 		= sanitize($mysqli, $_POST['email']); 
	$password	 		= mysqli_real_escape_string($mysqli, $_POST['password']); 
	
	$query  = "SELECT * FROM teacher WHERE email = '$email' OR teacher_id = '$teacher_id' "; 				
	$result = $mysqli->query($query);
	$max_teachers = mysqli_fetch_array($result);  
	
	if (!is_null($max_teachers['email']) ||
			!is_null($max_teachers['teacher_id'])) {
		echo "<div class='result'><p>";
		echo "<strong>Teacher ID</strong> or <strong>Email</strong> already in use.";
		echo "<br>Teacher not added.<br>";
		echo "Please <a href='javascript:history.back(-1)'>go back</a> and provide a different email.";
		echo "</p></div>";
	} 
	else if (empty($teacher_id) ||
					 empty($email)) {
		echo "<div class='result'><p>";
		echo "<strong>Teacher ID</strong> or <strong>Email</strong> is blank.";
		echo "<br>Teacher not added.<br>";
		echo "Please <a href='javascript:history.back(-1)'>go back</a> and provide a different email.";
		echo "</p></div>";
	}
	else { 
		$_SESSION['teacher_id'] = $teacher_id;
		$_SESSION['initial'] = TRUE;
		$_SESSION['logged_in'] = TRUE;	 
		$query  = "INSERT INTO teacher ";
		$query .= "(teacher_id, first_name, last_name, email)";
		$query .= "VALUES ";
		$query .= "('$teacher_id', '$first_name', '$last_name', '$email')";				 
		$mysqli->query($query); 
		
		$query  = "INSERT INTO teacher_log_in ";
		$query .= "(teacher_id, password) ";
		$query .= "VALUES ";
		$query .= "('$teacher_id', '$password')";				
		$mysqli->query($query); 
		
		echo '<div class="result">';
		echo '<h2>Registration Successful</h2>';
		echo "<strong>Teacher ID:</strong> $teacher_id<br>";
		echo "<strong>First Name:</strong> $first_name<br>";
		echo "<strong>Last Name:</strong> $last_name<br>";
		echo "<strong>Email:</strong> $email<br>";
		echo '</div>';				
?>
    <form action="" method="post" class="db-form-register-teacher">
    	<button type="submit">Get Started</button>
    </form>
<?php
	} 	
	mysqli_close($db);
?> 


<?php
	/* GET DATABASE */ 
	$db = Database::getInstance();
	$mysqli = $db->getConnection();
	
	/* VARIABLES */	
	// personal info 
	$student_id 	= sanitize($mysqli, $_POST['student_id']);
	$first_name 	= sanitize($mysqli, $_POST['first_name']);
	$last_name 		= sanitize($mysqli, $_POST['last_name']);
	$home_town 		= sanitize($mysqli, $_POST['home_town']); 
	$personality 	= sanitize($mysqli, $_POST['personality']);
	$interests 		= sanitize($mysqli, $_POST['interests']);
	$photo 				= $_FILES['photo']['name'];
	$photo_error 	= $_FILES['photo']['error'];
	$photo_path 	= '/students/images/';
	
	$number_of_emails = sanitize($mysqli, $_POST['number_of_emails']);
	for ($i=0; $i<=$number_of_emails; $i++) {  
		$emails[$i]['email'] = sanitize($mysqli, $_POST['emails'][$i]['email']);		 
	}
		
	//class info
	$major 										= sanitize($mysqli, $_POST['major']);
	$letter_of_recommendation = sanitize($mysqli, $_POST['letter_of_recommendation']);
	$graduating_year 					= sanitize($mysqli, $_POST['graduating_year']);
	
	//contact dates
	$number_of_contact_dates = sanitize($mysqli, $_POST['number_of_contact_dates']);
	$contact_dates = array();
	for ($i=1; $i<=$number_of_contact_dates; $i++) {
		$contact_dates[$i]['year'] 	= sanitize($mysqli, $_POST['contact_dates'][$i]['year']);
		$contact_dates[$i]['month'] = sanitize($mysqli, $_POST['contact_dates'][$i]['month']);
		$contact_dates[$i]['day'] 	= sanitize($mysqli, $_POST['contact_dates'][$i]['day']);
	}
	
	//courses
	$number_of_courses = $_POST['number_of_courses'];
	$courses = array();	
	for ($i=1; $i<=$number_of_courses; $i++) {
		$courses[$i]['course'] 		= sanitize($mysqli, $_POST['courses'][$i]['course']);
		$courses[$i]['semester']	= sanitize($mysqli, $_POST['courses'][$i]['semester']);
		$courses[$i]['grade'] 		= sanitize($mysqli, $_POST['courses'][$i]['grade']);
		$courses[$i]['quality'] 	= sanitize($mysqli, $_POST['courses'][$i]['quality']);
		$courses[$i]['absences'] 	= sanitize($mysqli, $_POST['courses'][$i]['absences']);
		$courses[$i]['late'] 			= sanitize($mysqli, $_POST['courses'][$i]['late']);
	}
	
	/* ERROR CHECKING */
	$check	= explode(", ", "student_id, first_name, last_name");
	$blanks = check_blank($check);

	/* MISSING REQUIRED FIELDS */	
	if(!empty($blanks)){
		show_blank($blanks);
	} 
	else {		
		/* MOVE FILE */
		try {
			move_uploaded_file($photo, $photo_path);
		} catch(Exception $e) {
			echo "Error uploading file: ".$photo_error;
		}
		if ($_POST['previous_step'] === 'add_student') {
			include_once('db.insertStudent.inc');
		}
		else {
			include_once('db.updateStudent.inc');
		}		
			
		echo '<div class="result">';	
		echo '<h2>PERSONAL INFO</h2>';
		echo '<strong>student_id:</strong> '.$student_id.'<br>';
		echo '<strong>first_name:</strong> '.$first_name.'<br>';
		echo '<strong>last_name:</strong> '.$last_name.'<br>';
		echo '<strong>home_town:</strong> '.$home_town.'<br>';
		echo '<strong>emails:</strong> '.$_POST['emails'][0]['email'].'<br>';
		echo '<strong>personality:</strong> '.$personality.'<br>';
		echo '<strong>interests:</strong> '.$interests.'<br>';
		echo '<strong>photo:</strong> '.$photo.'<br>';
		echo '<strong>photo_error:</strong> '.$photo_error.'<br>';
		echo '<strong>photo_path:</strong> '.$photo_path.'<br>';
		
		echo '<h2>ADDITIONAL EMAILS</h2>'; 
		echo "<strong>number_of_emails:</strong> ".$number_of_emails.'<br>';
		for ($i=1; $i<$number_of_emails; $i++) {
			echo "<strong>$i email:</strong> ".$emails[$i]['email'].'<br>'; 
		}
						
		echo '<h2>CLASS INFO</h2>';
		echo '<strong>major:</strong> '.$major.'<br>';
		echo '<strong>letter_of_recommendation:</strong> '.$letter_of_recommendation.'<br>';
		echo '<strong>graduating_year:</strong> '.$graduating_year.'<br>';
		
		echo '<h2>CONTACT DATES</h2>'; 
		echo "<strong>number_of_contact_dates:</strong> ".$number_of_contact_dates.'<br>';
		for ($i=1; $i<=$number_of_contact_dates; $i++) {
			echo "<strong>$i year:</strong> ".$contact_dates[$i]['year'].'<br>';
			echo "<strong>$i month:</strong> ".$contact_dates[$i]['month'].'<br>';
			echo "<strong>$i day:</strong> ".$contact_dates[$i]['day'].'<br>'; 
		}
		
		echo '<h2>COURSES</h2>';
		echo "<strong>number_of_courses:</strong> ".$number_of_courses.'<br>';
		for ($i=1; $i<=$number_of_courses; $i++) {
			echo "<strong>$i course :</strong> ".$courses[$i]['course'].'<br>';
			echo "<strong>$i semester:</strong> ".$courses[$i]['semester'].'<br>';
			echo "<strong>$i grade:</strong> ".$courses[$i]['grade'].'<br>';
			echo "<strong>$i quality:</strong> ".$courses[$i]['quality'].'<br>';
			echo "<strong>$i absences:</strong> ".$courses[$i]['absences'].'<br>';
			echo "<strong>$i late:</strong> ".$courses[$i]['late'].'<br>'; 
		}
		echo "</div>";
	}
	
	mysqli_close($db);
?>

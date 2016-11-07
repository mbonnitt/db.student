<?php
	$query  = "SELECT COUNT(student_id) FROM student WHERE student_id = $student_id"; 				
	$result = $mysqli->query($query);
	$max_students = mysqli_fetch_array($result);
	
	if ($max_students[0] > 0) {
		echo "$student_id is already in use.<br>";	
		echo "Student not added.<br>";
		echo "Please <a href='javascript:history.back(-1)'>go back</a> and provide a different Student ID.";
	} 
	else { 
		$query  = "INSERT INTO student ";
		$query .= "(student_id, first_name, last_name, home_town, photo_path, major, letter_of_recommendation, graduating_year)";
		$query .= "VALUES ";
		$query .= "('$student_id', '$first_name', '$last_name', '$home_town', '$photo', '$major', '$letter_of_recommendation', '$graduating_year')";				 
		$mysqli->query($query); 
		
		$query  = "INSERT INTO student_personality ";
		$query .= "(student_id, personality, interests) ";
		$query .= "VALUES ";
		$query .= "('$student_id', '$personality', '$interests')";				
		$mysqli->query($query); 			
		
		$query  = "INSERT INTO teacher_student ";
		$query .= "(teacher_id, student_id) ";
		$query .= "VALUES ";
		$query .= "('" . $_SESSION['teacher_id'] . "', '$student_id')";			
		$mysqli->query($query); 
			
		include_once('db.updateStudentSubTables.inc');
	}
?>
<h1>INSERT STUDENT</h1>

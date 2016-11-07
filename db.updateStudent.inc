<?php 
	$query  = "UPDATE student SET  ";
	$query .= "first_name = '$first_name', ";
	$query .= "last_name = '$last_name', ";
	$query .= "home_town = '$home_town', ";
	$query .= "photo_path = '$photo', ";
	$query .= "major = '$major', ";
	$query .= "letter_of_recommendation = '$letter_of_recommendation', "; 
	$query .= "graduating_year = '$graduating_year' ";
	$query .= "WHERE student_id = '$student_id'";		 
	$mysqli->query($query); 
	
	$query = "UPDATE student_personality SET ";	 
	$query .= "personality = '$personality', ";			
	$query .= "interests = '$interests' ";			
	$query .= "WHERE student_id = '$student_id'";			 
	$mysqli->query($query); 				
	
	$query = "DELETE FROM student_email WHERE student_id = '$student_id'";				
	$mysqli->query($query);
	
	$query = "DELETE FROM student_contact_date WHERE student_id = '$student_id'";				
	$mysqli->query($query); 
	
	$query = "DELETE FROM student_course WHERE student_id = '$student_id'";				
	$mysqli->query($query); 
	
	include_once('db.updateStudentSubTables.inc');
?>
<h1>UPDATE STUDENT</h1>

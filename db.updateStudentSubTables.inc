<?php
	for ($i=0; $i<=$number_of_emails; $i++) { 
		if ($emails[$i]['email'] != '') {
			$query  = "INSERT INTO student_email ";
			$query .= "(student_id, email) ";
			$query .= "VALUES ";
			$query .= "('$student_id', '".$emails[$i]['email']."')";				
			$mysqli->query($query); 
		}
	}
	
	for ($i=1; $i<=$number_of_contact_dates; $i++) {
		$contact_date = $contact_dates[$i]['year'] . '-' . $contact_dates[$i]['month'] . '-' . $contact_dates[$i]['day']; 
		$query  = "INSERT INTO student_contact_date ";
		$query .= "(student_id, contact_date) ";
		$query .= "VALUES ";
		$query .= "('$student_id', '$contact_date')";
		$mysqli->query($query); 					
	}
	
	for ($i=1; $i<=$number_of_courses; $i++) {			
		$query  = "INSERT INTO student_course ";
		$query .= "(student_id, course_id, semester, grade, absence, late, quality_of_work) ";
		$query .= "VALUES ";
		$query .= "('$student_id', '".$courses[$i]['course']."', '".$courses[$i]['semester']."', '".$courses[$i]['grade']."', '".$courses[$i]['absences']."', '".$courses[$i]['late']."', '".$courses[$i]['quality']."')";					
		$mysqli->query($query); 
	}		
?>

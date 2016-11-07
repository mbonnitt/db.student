<h1>View Student</h1>
<?php
	$db = Database::getInstance();
	$mysqli = $db->getConnection();		
	$limit_start = sanitize($mysqli, $_GET['start']) ?: 0;
	$limit_stop = sanitize($mysqli, $_GET['stop']) ?: 99;
	
	// get max students
	$query  = "SELECT COUNT(student_id) FROM student "; 
	$query .= "JOIN teacher_student ";
	$query .= "WHERE teacher_id = " . $_SESSSION['teacher_id'];
	$result = $mysqli->query($query);
	$max_students = mysqli_fetch_array($result);	 
	
	// get students
	$student_id = sanitize($mysqli, $_POST['student_id']) ?: sanitize($mysqli, $_GET['student_id']);
	$first_name = sanitize($mysqli, $_POST['first_name']) ?: sanitize($mysqli, $_GET['first_name']);
	$last_name = sanitize($mysqli, $_POST['last_name']) ?: sanitize($mysqli, $_GET['last_name']);
	
	if ($student_id != '' ||
			$first_name != '' ||
			$last_name != '') {
		$query  = "SELECT * FROM student ";
		$query .= "WHERE  ";	
		if ($student_id != '') { 
			$query .= "student_id LIKE '%$student_id%' ";
		}
		if ($first_name != '') {
			$query .= "first_name LIKE '%$first_name%' ";
		}
		if ($last_name != '') {
			$query .= "last_name LIKE '%$last_name%' ";
		}
		$query .= "AND student_id IN ( SELECT student_id FROM teacher_student ";
		$query .= "WHERE teacher_id = '" . $_SESSION['teacher_id'] . "' ) ";
		$query .= "ORDER BY last_name, first_name ";
		$query .= "LIMIT $limit_start, $limit_stop";
	}
	else {
		$query  = "SELECT * FROM student ";	 
		$query .= "WHERE student_id IN ( SELECT student_id FROM teacher_student ";	
		$query .= "WHERE teacher_id = '" . $_SESSION['teacher_id'] . "' ) "; 
		$query .= "ORDER BY last_name, first_name ";
		$query .= "LIMIT $limit_start, $limit_stop";				
	}
	$result = $mysqli->query($query);	   
	 
	echo get_arrows('view_student', $limit_start, $limit_stop, $max_students[0]);
	echo "<table class='table-view-student'><tbody>";
	echo "<tr><th>ID</th><th>First Name</th><th>Last Name</th><th colspan='2'>Actions</th></tr>";
	while ($student = mysqli_fetch_array($result)) { 
		echo "<form method='post' action='' id='view_student_form'>"; 
		echo "<input type='hidden' name='previous_step' value='view_student' />";
		echo "<input type='hidden' name='student_id' value='" . $student['student_id'] . "'";
		echo "<tr>";
		echo "<td>" . $student['student_id'] . "</td>";
		echo "<td>" . $student['first_name'] . "</td>";
		echo "<td>" . $student['last_name'] . "</td>";
		echo "<td>";
		echo "<button type='submit' name='step' value='update_student'>Update</button>";			
		echo "</td><td>";	
		echo "<button type='submit' name='step' value='delete_student' class='btn-delete'>Delete</button>";
		echo "</td></tr>";
		echo "</form>";
	}  		
	echo "</tbody></table>";	
	echo get_arrows('view_student', $limit_start, $limit_stop, $max_students[0]);
	mysqli_close($db); 
?>

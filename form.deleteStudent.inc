<h1>Delete Student</h1>
<?php
	if ($_POST['delete'] == 'delete_student_for_real') {
		$db = Database::getInstance();
		$mysqli = $db->getConnection();		
		$query = "DELETE FROM student WHERE student_id = '" . $_POST['student_id'] . "'";				
		$result = $mysqli->query($query);			
		mysqli_close($db);
		echo "<div class='result'><p class='text-emphasis'>Student deleted.</p></div>";
	}
	else {
		$db = Database::getInstance();
		$mysqli = $db->getConnection();		
		$query = "SELECT * FROM student WHERE student_id = '" . $_POST['student_id'] . "'";				
		$result = $mysqli->query($query);
		$student = mysqli_fetch_array($result);				
		mysqli_close($db);
?>
    <form action="" method="post" class="form-delete-student"> 
      <input type="hidden" name="student_id" value="<?php echo $student['student_id'] ?>" />
      <input type="hidden" name="step" value="delete_student" />
      <button type="submit" name="delete" value="delete_student_for_real" class="btn-delete">Yes, delete <?php echo $student['first_name'] . ' ' . $student['last_name'];?></button>  
    </form>    
    <form action="" method="post" class="form-delete-student">
      <button type="submit" name="step" value="<?php if ($_POST['previous_step'] != 'delete_student') { echo $_POST['previous_step']; } ?>" class="btn-cancel">No, go back!</button>
    </form>
<?php 
		}
?>

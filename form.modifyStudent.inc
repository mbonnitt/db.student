<h1>
<?php
if ($_POST['step'] == 'add_student') {
	echo 'Add ';
} 
else {
	echo 'Update ';
}
?>
Student</h1>
<?php
	if (!empty($_POST)
		&& $_POST['student_id'] != '') {
		$step = 'update_student';
		$db = Database::getInstance();
		$mysqli = $db->getConnection();		
		$query  = "SELECT * FROM student ";
		$query .= "JOIN student_personality ";
		$query .= "WHERE student.student_id = '" . $_POST['student_id'] . "'";
		$query .= "AND student.student_id = student_personality.student_id"; 
		$result = $mysqli->query($query);  
		$student = mysqli_fetch_array($result);   
		mysqli_close($db);   
	} 
	else {
		$step = 'add_student';
	}
?>
<form action="" method="post" enctype="multipart/form-data" class="form-modify-student"> 
	<input type="hidden" name="previous_step" value="<?php echo $step; ?>" />
	<fieldset>
		<legend>Student Info</legend>
	
		<!-- 
			PERSONAL INFO 
		-->
		<fieldset>
			<legend>Personal Info</legend>
			<div class="required">
				<label for="student_id">Student ID</label>
				<input type="text" name="student_id" value="<?php if(!empty($student['student_id'])) 
				echo $student['student_id']; ?>" required maxlength="7" class="input-student-id" />
			</div>
			<div class="required">
				<label for="first_name">First Name</label>
				<input type="text" name="first_name" value="<?php if(!empty($student['first_name'])) 
				echo $student['first_name']; ?>" required maxlength="50" />
			</div>
			<div class="required">
				<label for="last_name">Last Name</label>
				<input type="text" name="last_name" value="<?php if(!empty($student['last_name'])) 
				echo $student['last_name']; ?>" required maxlength="50" />
			</div>
			<div>
				<label for="home_town">Hometown</label>
				<input type="text" name="home_town" value="<?php if(!empty($student['home_town'])) 
				echo $student['home_town']; ?>" maxlength="35" />
			</div>           
      <?php 
				if(isset($student['student_id'])){
					$db = Database::getInstance();
					$mysqli = $db->getConnection();                
					$query  = "SELECT * FROM student_email ";
					$query .= "WHERE student_id = '" . $student['student_id'] . "'";
					$result = $mysqli->query($query);  
					$student_emails = mysqli_fetch_all($result, MYSQLI_ASSOC);  
				}  
				$number_of_emails = sizeof($student_emails) ?: 1; 
				mysqli_close($db);    
			?>
			<div class="required">
				<label for="emails[0][email]">Email</label>
				<input type="email" name="emails[0][email]" value="<?php if(!empty($student_emails[0]['email'])) 
				echo $student_emails[0]['email']; ?>"  required />
			</div>     
			<div>
				<label for="personality">Personality</label>
				<input type="text" name="personality" value="<?php if(!empty($student['personality'])) 
				echo $student['personality']; ?>" />
			</div>
			<div>
				<label for="interests">Interests</label> 
				<textarea name="interests"><?php if(!empty($student['interests'])) 
				echo $student['interests']; ?></textarea>
			</div>
			<div>
				<label for="photo">Photo</label>
				<input type="file" name="photo" />
			</div>
		</fieldset>
    
    <!--
    	ADDITIONAL EMAIL
    -->
    <fieldset>
    	<legend>Additional Emails</legend>  
				<input type="hidden" name="number_of_emails" id="number_of_emails" value="<?php echo $number_of_emails; ?>" /> 
        <?php
					for ($i=1; $i<$number_of_emails; $i++) { 
						echo create_field_email($i, $student_emails[$i]['email']);
					} 
				?>
				<input class="btn-add-field" type="button" id="btn_add_email" onclick="addEmail();" value="Add Email" />
    </fieldset>
		
		<!-- 
			CLASS INFO 
		-->
		<fieldset>
			<legend>Class Info</legend>  
			<div>
				<label for="major">Major</label>
				<input type="text" name="major" value="<?php if(!empty($student['major'])) echo $student['major']; ?>" maxlength="25" />
			</div>    
			<div>
				<label for="letter_of_recommendation">Letter of Recommendation</label>
				<select name="letter_of_recommendation">
					<option value="">---</option>
					<option value="0"
						<?php 
						if(isset($student['letter_of_recommendation']) 
							&& $student['letter_of_recommendation'] == '0'){ 
							echo " selected "; 
						} 
						?>
					>No</option>
					<option value="1" 
						<?php 
              if(!empty($student['letter_of_recommendation']) 
                && $student['letter_of_recommendation'] == '1'){ 
                echo " selected "; 
              } 
            ?>
					>Yes</option>
				</select>
			</div>
			<div>
				<label for="graduating_year">Graduating Year</label>
				<select name="graduating_year">
					<?php   
						echo create_drop_down_number($_THIS_YEAR, $_THIS_YEAR+6, 'down', $student['graduating_year']);
					?>   
				</select>
			</div>
		</fieldset>
		
		<!-- 
			CONTACT DATES
		-->
		<fieldset id="dates">
			<legend>Contact Dates</legend>
			<div class="table table-dates">
				<div class="row first headings">
					<div class="cell first"><span>&nbsp;</span></div>
					<div class="cell"><span>Month</span></div>
					<div class="cell"><span>Day</span></div>
					<div class="cell"><span>Year</span></div> 
				</div>
				<?php 
					if(isset($student['student_id'])){
						$db = Database::getInstance();
						$mysqli = $db->getConnection();                
						$query  = "SELECT * FROM student_contact_date ";
						$query .= "WHERE student_id = '" . $student['student_id'] . "'";
						$result = $mysqli->query($query);  
						$student_contact_dates = mysqli_fetch_all($result, MYSQLI_ASSOC);  
					}  
					$number_of_contact_dates = sizeof($student_contact_dates) ?: 0; 
					mysqli_close($db);     
				?>
				<input type="hidden" name="number_of_contact_dates" id="number_of_contact_dates" value="<?php echo $number_of_contact_dates; ?>" /> 
        <?php
					for ($i=0; $i<$number_of_contact_dates; $i++) {
						$j = $i + 1; 
						echo create_field_date($j, $student_contact_dates[$i]['contact_date']);
					}
				?>
				<input class="btn-add-field" type="button" id="btn_add_date" onclick="addDate();" value="Add Date" />
			</div>
		</fieldset>
	
		<!-- 
			COURSES
		-->
		<fieldset id="courses">
			<legend>Courses</legend>
			<div class="table table-courses">
				<div class="row first headings">
					<div class="cell first"><span>&nbsp;</span></div>
					<div class="cell"><span>Course #</span></div>
					<div class="cell"><span>Semester</span></div>
					<div class="cell"><span>Grade</span></div>
					<div class="cell"><span>Quality</span></div>
					<div class="cell"><span>Absences</span></div>
					<div class="cell"><span>Late</span></div>
				</div>
				<?php
					if(isset($student['student_id'])){
						$db = Database::getInstance();
						$mysqli = $db->getConnection();                
						$query = "SELECT * FROM student_course WHERE student_id = '" . $student['student_id'] . "'";	 
						$result = $mysqli->query($query);  
						$student_courses = mysqli_fetch_all($result, MYSQLI_ASSOC);  
					}
					$number_of_courses = sizeof($student_courses) ?: 0; 
					mysqli_close($db);      
				?>
				<input type="hidden" name="number_of_courses" id="number_of_courses" value="<?php echo $number_of_courses; ?>" />     
        <?php
					for ($i=0; $i<$number_of_courses; $i++) {
						$j = $i + 1; 
						echo create_field_course($j, $student_courses[$i]['course_id'], $student_courses[$i]['semester'], $student_courses[$i]['grade'], $student_courses[$i]['quality_of_work'], $student_courses[$i]['absence'], $student_courses[$i]['late'] );
					}
				?>
				<input class="btn-add-field" type="button" id="btn_add_course" onclick="addCourse();" value="Add Course" />  
			</div>  
		</fieldset>      
	</fieldset>
	<button type="submit" name="step" value="update_database">
	<?php 
	if ($_POST['step'] == 'add_student') { 
		echo 'Add '; 
	} 
	else { 
		echo 'Update '; 
	} 
	?>
  Student
  </button>
</form> 
<script src="js/form.functions.js"></script> 

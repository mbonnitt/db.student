<?php 
include_once('class.Database.inc');

if (isset($_POST['action']) && !empty($_POST['action']) &&
		isset($_POST['number']) && !empty($_POST['number'])) {
	$action = $_POST['action'];
	$number = $_POST['number'];
	switch($action){
		case 'create_field_course' : 
			echo create_field_course($number);
			break;
		case 'create_field_date' : 
			echo create_field_date($number);
			break;
		case 'create_field_email' : 
			echo create_field_email($number);
			break;
	}
} 

/**
* Return sanitized string for mysqli
* @param db connection $conn 
* @param string $input
* @return string 
*/
function sanitize($conn, $input) {	 
	return htmlspecialchars( strip_tags( mysqli_real_escape_string($conn, $input) ) );
}

/**
* Get forward backward arrows for db results
* @param string $step
* @param int $curr_start 
* @param int $curr_stop 
* @param int $last_stop
* @param int $max_on_page. Optional.
* @return string $field
*/
function get_arrows($step, $curr_start, $curr_stop, $last_stop, $max_on_page=100) {
	$field = "";
	$field .= "<div class='nav'>"; 
	if ($curr_start > 0) {
		$pre_start = $curr_start - $max_on_page;
		if ($pre_start < 0) {
			$pre_start = 0;
		}
		$pre_stop = $curr_start - 1;
		if ($pre_stop < $max_on_page) {
			$pre_stop = $max_on_page - 1;
		}
		$field .= "<a href='?step=$step&start=$pre_start&stop=$pre_stop'>Prev</a>";
	}
	if ($curr_stop < $last_stop) {
		$next_start = $curr_stop;
		if ($next_start > $last_stop) {
			$next_start = $last_stop;
		}
		$next_stop = $curr_stop + $max_on_page;
		if ($next_stop > $last_stop) {
			$next_stop = $last_stop;
		}
		$field .= "<a href='?step=$step&start=$next_start&stop=$next_stop'>Next</a>";
	}
	$field .= "</div>"; 
	return $field;
}
	
/**
* Return blank fields included in $vars
* @param  array $vars 
* @return array $blank
*/
function check_blank($vars) {	 
	$blank = array();
	$vars_length = count($vars);
	for ($i=0; $i<$vars_length; $i++) { 
		if (empty($_POST[$vars[$i]]) || str_replace(" ", "", $_POST[$vars[$i]]) == '') {
			$blank[] = $vars[$i];
		}
	}
	return $blank;
}

/**
* Outputs $vars to the screen
* @param array $vars
*/
function show_blank($vars) {
	for ($i=0; $i<count($vars); $i++) {
		echo ucwords(str_replace("_", " ", $vars[$i])) . " is blank.<br />";
	}
}

/**
* Create string of semester options
* @param int $num_semesters
* @param string $semester. Optional.
* @return string $field
*/
function create_drop_down_semester($num_semesters, $semester='') {
	$selected = "";
	$field = "";   
	$abbr_year = date('Y') - 2000; 
	$field .= "<option value=''>---</option>";
	for ($j=0; $j<$num_semesters; $j++) {
		for ($i=0; $i<2; $i++) {
			if ($i == 0) {
				$curr_year = $abbr_year - $j;
				$curr_semester = 'FA' . $curr_year;
			}
			else {					
				$curr_year = $abbr_year - $j;
				$curr_semester = 'SP' . $curr_year;
			}		
			if ($curr_semester === $semester) {
				$selected = 'selected';
			}
			else {
				$selected = '';
			}
			$field .= "<option value='$curr_semester' $selected>$curr_semester</option>";
		}
		 
	}
	return $field;
}

/*
* Create string of number options
* @param int $stop_num
* @param int $start_num. Optional.
* @param string $up_down. Optional.
* @param string $selected_number. Optional.
* @return string $field
*/
function create_drop_down_number($stop_num, $start_num = 0, $up_down = 'up', $selected_number = '') {
	$selected = "";
	$field = "";
	$field .= "<option value=''>---</option>";
	if (((int)$stop_num - (int)$start_num) > 50) {
		$field .= "<option value=''>NUMBER TOO BIG</option>";
	}
	else {
		if (strtolower($up_down) === 'up') { 
			for ($j=$start_num; $j<=$stop_num; $j++) { 
				if ($j === (int)$selected_number
					&& $selected_number != '') {
					$selected = 'selected';
				}
				else {
					$selected = '';
				}
				$field .= "<option value='$j' $selected>$j</option>";
			}
		} 
		else {			
			for ($j=$start_num; $j>=$stop_num; $j--) { 				
				if ($j === (int)$selected_number 
					&& $selected_number != '') {
					$selected = 'selected';
				}
				else {
					$selected = '';
				}
				$field .= "<option value='$j' $selected>$j</option>";
			}
		}
	}
	return $field;
}

/**
* Create string of month options
* @param string $month. Optional
* @return string $field
*/
function create_drop_down_months($month = '') {	
	$selected = "";
	$field = "";
	$field .= "<option value=''>---</option>";
	$months = array('Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec');
	for($j=1;$j<=12;$j++){
		if ($j === $month) {
			$selected = "selected";
		}
		else {
			$selected = "";
		}
		$field .= "<option value='$j' $selected>".$months[$j-1]."</option>";
	}
	return $field;
}

/**
* Create string of grade options
* @param string $grade. Optional
* @return string $field
*/
function create_drop_down_grade($grade) {
	
	$selected = "";
	$grades = array('A', 'A-', 'B+', 'B', 'B-', 'C+', 'C', 'C-', 'D+', 'D', 'D-', 'F', 'W');
	$number_of_grades = sizeof($grades);
	$field = ""; 
	$field .= "<option value=''>---</option>";
	for ($i=0; $i<$number_of_grades; $i++) {
		if ($grades[$i] === $grade) {
			$selected = "selected";
		}
		else {
			$selected = "";
		}
		$field .= "<option value='" . $grades[$i] . "' $selected>" . $grades[$i] . "</option>";
	}
	return $field;
} 

/**
* Creates a string of course options
* @param string $course_id. Optional.
* @return string $field
*/
function create_drop_down_course($course_id=''){
	$selected = "";
	$db = Database::getInstance();
	$mysqli = $db->getConnection();
	$query = "SELECT * FROM course";
	$result = $mysqli->query($query);	
	$field = "";
	$field .= "<option value=''>---</option>";
	while ($course = mysqli_fetch_array($result)) {
		if ($course['course_id'] === $course_id) {
			$selected = "selected";
		}
		else {
			$selected = "";
		}
		$field .= "<option value='".$course['course_id']."' $selected>".$course['course_id']."</option>"; 
	} 
	return $field;
}

/**
* Creates a string of performance options
* @param string $quality. Optional.
* @return string $field
*/
function create_drop_down_performance($quality=''){
	$selected = "";
	$performance_parts = array('Very Good', 'Good', 'Fair', 'Poor', 'Very Poor');
	$number_of_performance_parts = sizeof($performance_parts);
	$field = ""; 
	$field .= "<option value=''>---</option>";
	for ($i=0; $i<$number_of_performance_parts; $i++) {
		if ($performance_parts[$i] === $quality) {
			$selected = "selected";
		}
		else {
			$selected = "";
		}
		$field .= "<option value='" . $performance_parts[$i] . "' $selected>" . $performance_parts[$i] . "</option>";
	}
	return $field;
}

/**
* Creates date dropdowns
* @param int $i
* @param string $date. Optional.
* @return string $field
*/
function create_field_date($i, $date='date') {
	$year = '';
	$month = '';
	$day = ''; 
	if ($date != 'date') {
		$date_parts = explode('-', $date);
		$year = (int)$date_parts[0];
		$month = (int)$date_parts[1];
		$day = (int)$date_parts[2];
	}
	$field_id = "field_date_$i";
	$field = ""; 
	$field .= "<div class='added-field row' id='$field_id'>";
	$field .= "<div class='cell first'>";
	$field .= "<label for='contact_dates[$i][month]'>Contact Date $i</label>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>";
	$field .= "<select name='contact_dates[$i][month]'>";
	$field .= create_drop_down_months($month);
	$field .= "</select>";
	$field .= "</div>"; 
	$field .= "<div class='cell'>";
	$field .= "<select name='contact_dates[$i][day]'>";
	$field .= create_drop_down_number(31, 0, 'up', $day);
	$field .= "</select>";
	$field .= "</div>"; 
	$field .= "<div class='cell'>";
	$field .= "<select name='contact_dates[$i][year]'>";
	$field .= create_drop_down_number(date('Y'), 2013, 'up', $year);
	$field .= "</select>";
	$field .= "</div>";
	$field .= "<div class='cell'>";
	$field .= "<div class='btn-delete-field' onclick='removeDate($i)'></div>";
	$field .= "</div>";
	$field .= "</div>";  
  return $field;
}

/**
* Creates email input
* @param int $i
* @param string $email. Optional.
* @return string $field
*/
function create_field_email($i, $email='') { 
	$field_id = "field_email_$i";
	$field = ""; 
	$field .= "<div class='added-field' id='$field_id'>"; 
	$field .= "<label for='emails[$i]'>Alt Email $i</label>";  
	$field .= "<input type='email' name='emails[$i][email]' value='$email' />"; 
	$field .= "<div class='btn-delete-field' onclick='removeEmail($i)'></div>"; 
	$field .= "</div>";  
  return $field;
}

/**
* Creates course dropdowns
* @param int $i
* @param string $course_id. Optional.
* @param string $semester. Optional.
* @param string $grade. Optional.
* @param string $quality_of_work. Optional.
* @param string $absence. Optional.
* @param string $late. Optional.
* @return string $field
*/
function create_field_course($i, $course_id='', $semester='', $grade='', $quality_of_work='', $absence='', $late='') { 
	$field_id = "field_course_$i";
	$field = "";
	$field .= "<div class='added-field row' id='$field_id'>"; 
	$field .= "<div class='cell first'>"; 
	$field .= "<label for='courses[$i][course]'>Course $i</label>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][course]'>";
	$field .= create_drop_down_course($course_id);	 
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][semester]>'>";
	$field .= create_drop_down_semester(4, $semester); 
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][grade]'>";
	$field .= create_drop_down_grade($grade);	
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][quality]'>";		
	$field .= create_drop_down_performance($quality_of_work); 
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][absences]'>";			
	$field .= create_drop_down_number(8, 0, 'up', $absence); 
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>"; 
	$field .= "<select name='courses[$i][late]'>"; 
	$field .= create_drop_down_number(15, 0, 'up', $late);	
	$field .= "</select>"; 
	$field .= "</div>"; 
	$field .= "<div class='cell'>";
	$field .= "<div class='btn-delete-field' onclick='removeCourse($i)'></div>";
	$field .= "</div>";
	$field .= "</div>"; 
	return $field;
}
	
?>

<h1>Search Student</h1>
<form action="" method="post" class="form-search-student">
	<fieldset>
  	<legend>Student Info</legend>
    <p>Search using one or more of the following fields.</p>
    <div>
      <label for="student_id">Student ID</label>
      <input type="text" name="student_id" class="input-student-id" maxlength="7" />
    </div>
    <div>
      <label for="first_name">First Name</label>
      <input type="text" name="first_name" maxlength="50" />
    </div>
    <div>
      <label for="last_name">Last name</label>
      <input type="text" name="last_name" maxlength="50" />
    </div>
  </fieldset>
  <button type="submit" name="step" value="view_student">Search</button>
</form>

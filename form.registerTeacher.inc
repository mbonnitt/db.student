<h1>Register Teacher</h1> 
<form action="" method="post" class="add_teacher_form">   
  <fieldset>
    <legend>Teacher Info</legend> 
    <div class="required">
      <label for="teacher_id">Teacher ID</label>
      <input type="text" name="teacher_id" required class="input-student-id" maxlength="7" />
    </div>
    <div class="required">
      <label for="first_name">First Name</label>
      <input type="text" name="first_name" required />
    </div>
    <div class="required">
      <label for="last_name">Last Name</label>
      <input type="text" name="last_name" required />
    </div> 
    <div class="required">
      <label for="email">Email</label>
      <input type="email" name="email" required />
    </div>
    <div class="required">
      <label for="password">Password</label>
      <input type="password" name="password" required />
    </div>
  </fieldset> 
  <button type="submit" name="step" value="db_register_teacher">Register</button>
</form>
<form action="" method="post">
	<button type="submit" class="btn-de-emphasis">Login</button>
</form>
      

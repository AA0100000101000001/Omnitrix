
//Mode 3
//Function for transformation
void transformedMode() {

  //Check transformation time
  //Transformation time is done while omnitrix does not sleep
  if ((RTC_getLocalEpoch() - transformation_start_time) > ALIEN_TRANSFORMATION_TIME_TEST) {

    //Go to next mode
    mode3to4();

  //Transformation time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;
  }
}

//Mode 4
//Recharge mode
void rechargeMode() {

  //Check recharging time
  //Recharging time is done
  if ((RTC_getLocalEpoch() - recharging_start_time) > OMNITRIX_RECHARGE_TIME_TEST) {
      
    //Go to first mode
    mode4to1();

  //Recharging time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;
  }
  
}

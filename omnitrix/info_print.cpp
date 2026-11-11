
#include "info_print.h";

//VERBOSE ANIMATION INFO
//Saves in the variable the current time if verbose animation info is enabled
void verbose_anim_info_save_anim_time(unsigned long *start_frame_time) {
#if defined ENABLE_VERBOSE_ANIM_INFO
  *start_frame_time = get_anim_time();
#endif
}
/*
//Saves frame_duration_time, frame_duration_since_start and does avrg_frame_time calculation
void verbose_anim_info_end_frame_wrapper(
  unsigned long *start_frame_time, 
  unsigned long *frame_duration_time, 
  unsigned long *frame_duration_since_start) {

}*/

// Function print_verbose_anim_info_end_frame: prints info at the end of a frame
// Prints frame_duration_time, frame_duration_since_start, does avrg_frame_time calculation 
//If animation with images is used also shows frame_decod_duration_time
#if defined START_ANIMATION_WITH_IMAGES
void print_verbose_anim_info_end_frame(
  unsigned long *start_frame_time, 
  //unsigned long *frame_duration_time, 
  //unsigned long *frame_duration_since_start, 
  //unsigned long *frame_decod_duration_time) { //, 
  unsigned long *start_frame_decod_time) {
#if defined ENABLE_VERBOSE_ANIM_INFO

  unsigned long frame_duration_time = get_anim_time() - *start_frame_time;
  unsigned long frame_duration_since_start = get_anim_time() - g_anim_start;
  avrg_frame_time += (double) frame_duration_time;
  
  unsigned long frame_decod_duration_time = get_anim_time() - *start_frame_decod_time;
  avrg_frame_decod_time += frame_decod_duration_time;
  Serial.printf("Time passed since frame decoded: %d, time passed since frame real time: %d, total time since start: %d\n", 
        frame_decod_duration_time, frame_duration_time, frame_duration_since_start);
#endif
}

#elif defined START_ANIMATION_WITHOUT_IMAGES
void print_verbose_anim_info_end_frame(
  unsigned long *start_frame_time) {
  //, unsigned long *frame_duration_time, unsigned long *frame_duration_since_start) {

  //Serial.printf("Time passed since frame real time: %d micros, total time since start: %d micros\n", frame_duration_time, frame_duration_since_start);
}
#endif

// Function verbose_anim_end_info: prints info at the end of the animation
// Prints Average frame rate, Total start_animation time length and if animation with images is enabled Average frame decode time
#if defined START_ANIMATION_WITH_IMAGES
void verbose_anim_end_info() {
#if defined ENABLE_VERBOSE_ANIM_INFO

    unsigned long end_animation_time = get_anim_time();
    Serial.printf("Average frame rate: %.2f, Average frame decode time: %.2f\n", 
      avrg_frame_time/(OMNITRIX_ANIM_FRAME_LAST_INDEX + 1), 
      avrg_frame_decod_time/(OMNITRIX_ANIM_FRAME_LAST_INDEX + 1));
    Serial.printf("Total start_animation time length : %d\n", end_animation_time - g_anim_start);
#endif
}
#elif defined START_ANIMATION_WITHOUT_IMAGES
void verbose_anim_end_info() {
#if defined ENABLE_VERBOSE_ANIM_INFO

#endif
}
#endif
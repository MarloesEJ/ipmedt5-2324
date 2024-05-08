<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\PageController;
use App\Http\Controllers\ArduinoController;

Route::get('/', [PageController::class, 'index']);
Route::get('/plantPage', [PageController::class, 'plantPage']);
Route::get('/plusLevel',[PageController::class, 'plusLevel']);
Route::get('/minLevel', [PageController::class, 'minLevel']);
Route::get('/setAutomation', [PageController::class, 'setAutomation']);
Route::get('/giveWater', [PageController::class, 'giveWater']);

//give data to arduino
Route::get('/get_Automation_state', [ArduinoController::class, 'get_Automation_state']);
Route::get('/get_Level_state', [ArduinoController::class, 'get_Level_state']);
Route::get('/get_giveWater_state', [ArduinoController::class, 'get_giveWater_state']);
Route::get('/get_measurement', [ArduinoController::class, 'get_measurement']);

//recieve data from arduino
Route::get('/plus_pressed', [ArduinoController::class, 'plus_pressed']);
Route::get('/min_pressed', [ArduinoController::class, 'min_pressed']);
Route::get('/auto_pressed', [ArduinoController::class, 'auto_pressed']);
Route::get('/water_given', [ArduinoController::class, 'water_given']);
Route::get('/moisture_state/{number}', [ArduinoController::class, 'get_moisture_state']);

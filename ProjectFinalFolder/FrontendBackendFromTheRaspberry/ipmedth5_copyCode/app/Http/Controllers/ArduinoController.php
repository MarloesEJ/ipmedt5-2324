<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\level;
use App\Models\measurement;
use App\Models\give_water;
use App\Models\automation;

class ArduinoController extends Controller
{
    public function get_Automation_state(){
        return automation::first()->is_on;
    }

    public function get_Level_state(){
        return level::first()->level;
    }

    public function get_giveWater_state(){
        return give_water::first()->give_water;
    }

    public function plus_pressed(){
        $levels = level::first();
        if($levels->level<9){
            $levels->level += 1;
        }
        $levels->save();
        // return redirect('/plantPage');
    }

    public function min_pressed(){
        $levels = level::first();
        if($levels->level>0){
            $levels->level -= 1;
        }
        $levels->save();
        // return redirect('/plantPage');
    }

    public function auto_pressed(){
        $automation = automation::first();
        if($automation->is_on == 1){
            $automation->is_on = 0;
        }
        else{
            $automation->is_on = 1;
        }
        $automation->save();
    }

    public function water_given(){
        $give_water = give_water::first();
        if($give_water->give_water==1){
            $give_water->give_water = 0;
        }
        $give_water->save();
    }

    public function get_moisture_state($number){
        $measurement = measurement::first();
        $measurement->measurement = $number;
        $measurement->save();
    }

    public function get_measurement(){
        return measurement::first()->measurement;  
    }

}

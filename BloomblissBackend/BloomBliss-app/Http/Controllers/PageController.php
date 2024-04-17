<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\level;
use App\Models\measurement;
use App\Models\give_water;
use App\Models\automation;

class PageController extends Controller
{
    function index(){
        return view('home');
    }

    function plantPage(){
        $levels = level::first();
        $measurements = measurement::first();
        $give_water = measurement::first();
        $automation = automation::first();
        return view('plantPage')->with('level', $levels)->with('measurement', $measurements)->with('automation', $automation);
    }

    public function plusLevel(){
        $levels = level::first();

        if($levels->level<9){
            $levels->level += 1;
        }

        $levels->save();
        return redirect('/plantPage');
    }

    public function minLevel(){
        $levels = level::first();
        if($levels->level>1){
            $levels->level -= 1;
        }
        $levels->save();
        return redirect('/plantPage');
    }

    public function setAutomation(){
        $automation = automation::first();
        if($automation->is_on == 1){
            $automation->is_on = 0;
        }
        else{
            $automation->is_on = 1;
        }
        $automation->save();
        return redirect('/plantPage');
    }

    public function giveWater(){
        $give_water = give_water::first();
        if($give_water->give_water==0){
            $give_water->give_water = 1;
        }
        $give_water->save();
        return redirect('/plantPage');
    }

}

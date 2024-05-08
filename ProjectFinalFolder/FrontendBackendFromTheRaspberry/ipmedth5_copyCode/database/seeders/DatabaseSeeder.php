<?php

namespace Database\Seeders;

use App\Models\User;
// use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use DB;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     */
    public function run(): void
    {
        DB::table('levels')->insert([
            'plant_name' => 'monstera',
            'level' => 0,
        ]);

        DB::table('measurements')->insert([
            'plant_name' => 'monstera',
            'measurement' => 0,
        ]);

        DB::table('automation')->insert([
            'plant_name' => 'monstera',
            'is_on' => 1, //1 is true, dus het moet water geven wanneer nodig
        ]);

        DB::table('give_water')->insert([
            'plant_name' => 'monstera',
            'give_water' => 0, //0 is false, dus nu geen extra water geven
        ]);
    }
}

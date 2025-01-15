import { globSync as glob } from 'glob';
import path from 'path';
import {Module, Result} from './utils';


// parse days
const days: string[] = [];
let day: string = "";
let day_n: number;

glob('./src/[0-9][0-9]/').map((p:string) => {
	day = path.basename(p)
	day_n = parseInt(day);
	if ( day_n >=2 && day_n <= 6 )
		days.push(day);
});


async function loadModules() {
	const modules: Module[] = await Promise.all(
		days.map(day =>  import(`./${day}/main`) as Promise<Module>)
	);
	return modules;
}


loadModules().then(modules => {
	 modules.forEach((m,i) => {
		m.main().then((res:Result) => console.log(days[i],res.sol1,"\t",res.sol2));
	});
});

//import assert from 'assert';
import * as path from 'path';


import {read, ParsedData, get_day, Result} from '../utils';

let DEBUG: number = 0;
type Vector2 = [number, number]
type Matrix2 = [Vector2, Vector2]
type Matrix = number[][]
type Mat = Cell[][]
const dirs_char = [
	[[0,-1],"<"],
	[[1,0], "v"],
	[[0,1], ">"],
	[[-1,0], "^"]
]

interface ParsedData1 {
	gua: Vec2
	mat: Mat
}

interface Passage {
	step: number
	dir: Vec2
}

class Cell {
	constructor(public s: number, public p: Passage[]) {}
}

class Vec2 {
	private rot_c: Matrix2;
	private rot_a: Matrix2;
	private vec: Vector2;

	constructor(public x: number, public y: number) {
		this.x=x;
		this.y=y;
		this.vec= [0,0];
		this.vec[0] = x;
		this.vec[1] = y;
		this.rot_c = [[0,1],[-1,0]];
		this.rot_a = [[0,-1],[1,0]];
	}
	assign(x: number, y: number) {
		this.x=x;
		this.y=y;
		this.vec= [0,0];
		this.vec[0] = x;
		this.vec[1] = y;
	}

	toString() {
		return `x:${this.x} y:${this.y}`
	}

	outside1(mat: Matrix): boolean {
		return ( this.y >= mat[0].length || this.x >= mat.length || this.x <0 || this.y <0)
	}
	outside(mat: Mat): boolean {
		return ( this.y >= mat[0].length || this.x >= mat.length || this.x <0 || this.y <0)
	}
	copy(): Vec2 {
		return new Vec2(this.x, this.y);
	}
	add(other: Vec2): Vec2 {
		return new Vec2(this.x + other.x, this.y + other.y);
	}
	equal(other: Vec2): boolean {
		return (this.x === other.x && this.y === other.y);
	}
	rotate() {
		const res: number[] = this.rot_c.map((row:Vector2) => row.reduce((sum:number, val:number, i:number) => sum + val * this.vec[i], 0));
		return new Vec2(res[0],res[1]);
	}
}

//const matv = (m: Matrix2, v: Vector2): Vector2 => {
	//const r: number[] = m.map(row => row.reduce((sum:number, val:number, i:number) => sum + val * v[i], 0))
	//return [r[0], r[1]];
//};

const mat2txt = (matrix: Mat): string =>
		matrix.map(row => row.map(cell => {
		if (cell.p.slice(-1)[0]) 
			return cell.p.reduce((maxp:number, val:Passage) => Math.max(maxp,val.step),0).toString().padStart(2,'0');
		else return cell.s.toString().padStart(2,'0');
	}).join(' ')).join('\n')+"\n---------";


async function parse(input:ParsedData): Promise<ParsedData1> {
	try {
		var {lines, text, nrow, ncol} = input; 
		var gua: Vec2 = new Vec2(0,0);
		var size: Vec2 = new Vec2(0,0);
		var i: number = 0;
		var j: number = 0;
		const mat: Mat = Array.from({length: lines.length-1}, () => Array.from({length: lines[0].length}, () => new Cell(0,[])));

		lines.forEach((line:string,i:number) => {
			[...line].forEach((char:string,j:number) =>
			{
				if (char=="^") {
					gua.assign(i,j);
					mat[i][j] = {s:-2,p:[]}
				} else if (char=="#") {
					mat[i][j] = {s:-1,p:[]};
				} else {
					mat[i][j] = {s:0,p:[]};
				}
			});
		});
		size.assign(i,j);
		return {gua, mat};
	} catch (error) {
		throw error;
	}
}

function walk(gua:Vec2, dir:Vec2, mat :Mat, vis :Set<number>, path: Vec2[]) {
	let ng = gua.add(dir);
	if (ng.outside(mat)) return;

	if (mat[ng.x][ng.y].s==-1) {
		dir = dir.rotate();
		walk(gua,dir,mat,vis,path);
	} else {
		gua = ng;
		vis.add(gua.x*mat.length+gua.y);
		path.push(gua);
		mat[gua.x][gua.y].p.push({step:path.length,dir:dir});
		walk(gua,dir,mat,vis,path);
	}
	return;
}

function walk2loop(gua:Vec2, dir:Vec2, mat: Mat, layer: number, block: Vec2): boolean {
	// gua is current position of the guard known to be good
	
	// candidate next position
	let ng = gua.add(dir);
	// check if inside
	if (ng.outside(mat)) return false;

	let ret: boolean = false
	// check if new candidate has a previous passage matching direction which would result in loop
	mat[ng.x][ng.y].p.forEach((pass: Passage) => {
		if (!ret && (pass.step==layer || pass.step > 0) && pass.dir.equal(dir)) {
			ret=true;
		}
	});

	if (ret) return ret;

	// check if obstacle, include also newly added block
	if (mat[ng.x][ng.y].s==-1 || ng.equal(block)) {
		dir = dir.rotate();
		ret = walk2loop(gua,dir,mat,layer, block);
	} else {
		// update guard
		gua = ng;
		// log passage using layer from which the block was placed
		mat[gua.x][gua.y].p.push({step: layer, dir: dir});
		// initiate next step
		ret = walk2loop(gua,dir,mat,layer, block);
	}
	return ret;
}


function walk2(gua:Vec2, dir:Vec2, vis:Set<number>, path:Vec2[], mat:Mat) {
	// compute next position
	let ng = gua.add(dir);
	// check if inside
	if (ng.outside(mat)) return;


	if (mat[ng.x][ng.y].s==-1) {
		// if obstacle, discard candidate, update direction
		dir = dir.rotate();
		walk2(gua,dir,vis,path,mat);

	} else {
		// next cell exist and it is free to step
		//
		// what if there would be a block there
		// search for loops
		// ng is a position candidate for a new #

		// check if placing a block in ng would stop the past
		var visited: boolean = false;
		mat[ng.x][ng.y].p.forEach((pass) => {
			if (!visited && pass.step > 0)  visited=true;
		});
		const blockid: number = ng.x*mat.length+ng.y;

		let new_dir = dir.rotate();
		if (
			// initial guard position is not allowed
			!(mat[ng.x][ng.y].s==-2) &&
			// consider only if do not interrupt previous path
			!visited &&
			// check if end up in a loop, 
			// log progress in separate layer indexed by blockid
			walk2loop(gua,new_dir,mat, -blockid, ng)

		) vis.add(blockid);

		// update guard position
		gua = ng;
		// update path
		path.push(gua);
		// update mat after step
		mat[gua.x][gua.y].p.push({step: path.length, dir: dir});
		// go on
		walk2(gua,dir,vis,path,mat);
	}
}

async function solve1(input: ParsedData1, debug: boolean = false): Promise<number> {
	let res:number = 0;
	const {gua,mat} = input;
	var vis = new Set<number>();
	var dir = new Vec2(-1,0);
	var path: Vec2[] = [];
	vis.add(gua.x*mat.length+gua.y);
	mat[gua.x][gua.y].p.push({step:0,dir:dir});
	walk(gua,dir,mat,vis,path);
	if (debug) console.log(mat2txt(mat));
	res = vis.size;
	return res;
}

async function solve2(input: ParsedData1, debug: boolean = false): Promise<number> {
	let res:number = 0;
	const {gua,mat} = input;
	var vis = new Set<number>();
	var dir: Vec2 = new Vec2(-1,0);
	var path: Vec2[] = [];
	path.push(gua);
	mat[gua.x][gua.y].p.push({step:0,dir:dir});
	walk2(gua,dir,vis,path,mat);
	if (debug) console.log(mat2txt(mat));
	res = vis.size;
	return res;
}

async function main() {
	try {
		const dirPath = __dirname.replace("dist","data");
		const input : ParsedData = await read(path.join(dirPath, 'user1', 'input'));
		//const input_test : ParsedData = await read(path.join(dirPath, 'test', 'input'));
		//const input_test1 : ParsedData = await read(path.join(dirPath, 'test1', 'input'));
		//const input_test2 : ParsedData = await read(path.join(dirPath, 'test2', 'input'));
		var sol1: number = 0;
		var sol2: number = 0;

		//let sol1_test: number = await solve1(await parse(input_test), true);
		//console.log("Part1 test1:", sol1_test);
		//assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);

		sol1 = await solve1(await parse(input));

		//let sol2_test: number = await solve2(await parse(input_test), true);
		//console.log("Part2 test1:", sol2_test);
		//assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);

		//let sol2_test1: number = await solve2(await parse(input_test2));
		//console.log("Part2 test2:", sol2_test2);

		//let sol2_test2: number = await solve2(await parse(input_test3));
		//console.log("Part2 test3:", sol2_test3);

		sol2 = await solve2(await parse(input));

		return {sol1, sol2};
	} catch (error) {
		if (error instanceof Error) {
			throw new Error(`Failed to Solve: ${error.message}`);
		}
		throw error;
	}
}

if (require.main === module) {
	if (DEBUG) get_day(__dirname).then((day:number) => console.log(`Day ${day}`));
	main().then((res:Result) => { console.log(res.sol1); console.log(res.sol2);});

}

export {main};

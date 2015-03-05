module.exports = function(grunt) {
	grunt.loadNpmTasks('grunt-shell');
	grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.initConfig({
		shell: {
			greet: {
				command: function (greeting) {
					return 'echo ' + greeting;
				}
			},
			make: {
				command: 'make',
			},
			clean: {
				command: 'make clean',
			},
			execute: {
				command: './cdot test',
			},
			test: {
				command: 'pwd && tree -I "*.o|node_modules" && echo "SELECT * FROM dotfiles" && sqlite3 db.db "SELECT * FROM dotfiles;"',
			},
		},
		watch: {
			scripts: {
				files: ['**/*.c'],
					     tasks: ['run'],
					     options: {
					     spawn: false,
					     },
					     },
					     },
	});
	grunt.registerTask('default', ['watch']);
	grunt.registerTask('run', ['shell:clean', 'shell:make', 'shell:execute', 'shell:test']);
	grunt.registerTask('exec', ['shell:execute', 'shell:test']);
}

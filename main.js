import $ from "jquery"
window.$ = $;
import Vue from "vue";
import VueRouter from "vue-router";
Vue.use(VueRouter);
var index = require("./components/index.vue")
var topic = require("./components/topic.vue")
var collect = require("./components/collect.vue")
var router = new VueRouter({
    routers:[{
        path:"/index",
        component:index,
        children:[{
            path:"topic",
            component:topic
        },{
            path:"collect",
            component:collect
        }]
    }]
})
new vue ({
    el:"#demo",
    template:`
 <router-view></router-view>
    `
})
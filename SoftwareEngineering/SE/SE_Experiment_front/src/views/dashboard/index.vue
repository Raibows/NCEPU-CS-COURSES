<template>
  <div class="dashboard-container">
    <el-row style="margin: 20px" :gutter="20">
      <el-col :span="20">
        <panel-group/>
      </el-col>
      <el-col :span="4">
        <Introduce/>
      </el-col>
    </el-row>

  </div>

</template>

<script>

import PanelGroup from './components/PanelGroup'
import Introduce from "@/views/dashboard/components/Introduce";
import Table from "@/views/dashboard/components/Table";

export default {
  name: 'Dashboard',
  data() {
    return {
      tableData: [{
        date: '2016-05-02',
        name: '王小虎',
        address: '上海市普陀区金沙江路 1518 弄'
      }, {
        date: '2016-05-04',
        name: '王小虎',
        address: '上海市普陀区金沙江路 1517 弄'
      }, {
        date: '2016-05-01',
        name: '王小虎',
        address: '上海市普陀区金沙江路 1519 弄'
      }, {
        date: '2016-05-03',
        name: '王小虎',
        address: '上海市普陀区金沙江路 1516 弄'
      }]
    };
  },
  components: {
    PanelGroup,
    Introduce,
    Table
  },
  computed: {}
}
</script>

<style lang="scss" scoped>

</style>

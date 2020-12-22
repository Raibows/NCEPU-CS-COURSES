<template>
  <div>
    <p>{{title}}</p>
    <el-table
      :data="data"
      border
      style="width: 100%;">
      <el-table-column
        prop="date"
        label="日期"
        width="180">
      </el-table-column>
      <el-table-column
        prop="name"
        label="姓名"
        width="180">
      </el-table-column>
      <el-table-column
        prop="address"
        label="地址">
      </el-table-column>
    </el-table>
  </div>

</template>

<script>
export default {
  name: "Table",
  data() {
    return {}
  },
  props: ["data", "title"]
}
</script>

<style scoped>

</style>
